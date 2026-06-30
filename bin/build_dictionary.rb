# Program: build_dictionary.rb
#
# Purpose: Read any number of Inform 6 source code files, then create an 
# Inform 6 dictionary file, containing:
# * The constant holding the value ("factor") used for encoding the dictionary
# * A constant for each dictionary word used in the source code files.
#
# Note: Dictionary words that contain a space are not considered.
#
# E.g. "ruby build_dictionary.rb dict.inf source1.inf source2.inf"
# This creates a new file (overwriting it if it already exists!), called 
# dict.inf

if ARGV.length < 2
	puts "Sample usage: ruby build_dictionary.rb dictionary.inf mygame.inf parser.inf ..."
	puts "Note: This OVERWRITES dictionary.inf"
	exit 1
end

$dictionary_inf = ARGV[0]

####################################
# Extract words from source
####################################

$words = {}
word_count = 0
$filename = ""
$linenumber = 0
1.upto(ARGV.count - 1) do |argno|
	$filename = ARGV[argno]
	$linenumber = 0
	File.open($filename).each_line do |line|
		$linenumber += 1
		if line =~ /'[^ ']{2,}'/
			ix = 0
			while m = line.match(/'([^ ']{2,20})'(?:\s*=\s*W_([A-Z0-9_]+)\s*$)?/, ix)
				source_word = m[1].downcase
				const_name = nil
				const_name = m[2] if m.length > 2
				unless $words.has_key? source_word
					zscii_word = source_word.dup
					zscii_word = zscii_word[0] if zscii_word =~ /^.\/\/$/
					zscii_word.gsub!("^", "'")
					$words[source_word] = [zscii_word, const_name, $filename, $linenumber]
					word_count += 1
	#				puts "source_word: #{source_word} zscii_word: #{zscii_word}"
				end
				ix = m.end(0) + 1
			end
		end
	end
end

puts "#{word_count} different words found in source."

$chk2 = {}
$const = {}

$default_unicode = "äöüÄÖÜß»«ëïÿËÏáéíóúýÁÉÍÓÚÝàèìòùÀÈÌÒÙâêîôûÂÊÎÔÛåÅøØãñõÃÑÕæÆçÇþðÞÐ£œŒ¡¿"
$default_unicode_replacements = [
"ae","oe","ue","AE","OE","UE","ss","qstart","qend","edia","idia","ydia","EDIA","IDIA",
"aacute","eacute","iacute","oacute","uacute","yacute",
"AACUTE","EACUTE","IACUTE","OACUTE","UACUTE","YACUTE",
"agrave","egrave","igrave","ograve","ugrave",
"AGRAVE","EGRAVE","IGRAVE","OGRAVE","UGRAVE",
"acflex","ecflex","icflex","ocflex","ucflex",
"ACFLEX","ECFLEX","ICFLEX","OCFLEX","UCFLEX",
"aa","AA","oslash","OSLASH",
"atilde","ntilde","otilde","ATILDE","NTILDE","OTILDE",
"aelig","AELIG","cced","CCED",
"thorn","eth","THORN","ETH",
"pound","oelig","OELIG","exclaminv","questinv"
];

def calcChk2(str)
	s = 0
	str = str.downcase
	weird = (str =~ /[^a-z0-9\-']/)
	str.each_char do |c|
		v = c.ord
		if weird and v > 127
			i = $default_unicode.index(c)
			unless i
				puts "Unavailable character #{c} found in word #{str}!"
				exit 1
			end
			v = 155 + i
		end
		s = $factor * s
		s &= 0x7fff
		s = s + v
		s &= 0x7fff
	end
	s -= 2000 if s < 1024
	s
end

def addConst(source_word)
	arr = $words[source_word]
#	zscii_word = in_arr[0]
	const = nil # in_arr[1]
#	puts "ENTRY: #{word_entry}"
#	arr = [zscii_word] #word_entry.chomp.strip.downcase.split(/\|/)
	unless const
		if arr.length > 1 and arr[1]
#			puts arr
			const = arr[1].upcase 
		else
			const = arr[0].upcase.tr('-,/', '_').gsub(/'/,"_Q_").gsub(/__+/,"_")
			if const =~ /[^A-Z0-9\_']/
				res = ""
				const.each_char do |c|
					if c.ord > 127
						i = $default_unicode.index(c)
						unless i
							puts "addConst: Unavailable unicode character #{c} " + 
								"found in constant name #{const}!"
							exit 1
						end
						c = $default_unicode_replacements[i].upcase
					end
					res += c
				end
				const = res
			end
		end
	end
	if $const.has_key? const
		puts "ERROR: Constant W_#{const} has multiple entries!"
		puts $const.to_s
		exit 1
	elsif const =~ /[^A-Z0-9_]/
		puts "ERROR: Constant W_#{const} has illegal characters (Only A-Z, 0-9, _ are valid)!"
		exit 1
	end
	$const[const] = [calcChk2(arr[0]), arr[0], source_word]
	const
end

#######################################
# Find best dictionary encoding factor
#######################################

$score = Array.new(10001)

best = 1000000
$best_factor = 0
coll = []

14.upto(10000) do |i|
	$chk2 = {}
	$factor = i

	count = 0
	collisions = 0

	$words.values.each do |line|
		word = line[0] # .chomp.strip.downcase.split(/\|/)[0]
		if word.length > 0
			count += 1
#			print word
			c2 = calcChk2(word)
			if $chk2.has_key? c2
				collisions += 1
				collisions += 1 if $chk2[c2] !~ /.,./
#				break if collisions >= best
				$chk2[c2] += "," + word
	#			print word + "        Chk2:#{$chk2[c2]}\n"
			else
				$chk2[c2] = word
			end
	#		print "\n"
		end
	end

	if collisions < best
		best = collisions
		$best_factor = $factor
		coll = $chk2.values.select {|x| x =~ /.,./ }
		puts "$factor: #{$factor}, Collisions: #{collisions} " +
			"(#{(100 * collisions.to_f / count).round(2)}%)"
	end
	break if best == 0
end

#######################################
# Encode all words
#######################################

$factor = $best_factor

$words.keys.sort.each do |source_word|
	addConst(source_word)
end


#######################################
# Create/update dictionary.inf
#######################################

File.open($dictionary_inf, 'w') do |file|

	file.puts "System_file;\n\n"
	file.puts "Constant DICT_FACTOR = #{$factor};"


	if best == 0
		file.puts "\n! No collisions\n\n"
	else
		file.puts "\n! Collisions:\n"
		coll.each do |e|
			file.puts "!   #{e}"
		end
		file.puts "\n"
	end

	$const.keys.sort.each do |c|
		arr = $const[c]
		comment = " ! #{arr[1]}"
		if arr[1] != arr[2]
			comment = " ! #{arr[1]}|#{arr[2]}"
		end
		file.puts "Constant W_#{c} = #{arr[0]};#{comment}"
	end

end

