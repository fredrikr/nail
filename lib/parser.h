System_file;

! ####################################
!  Word constants
! ####################################

! 'to' = W_TO_WORD
! './/' = W_PERIOD_WORD

! ####################################
!  Supporting routines
! ####################################

[ YesOrNo n;
	for (::) {
		_ReadPlayerInput(true, true);
		n = parse2 -> 1;
		parse2 -> 1 = 0;
		if(n == 1) {
			! one word reply
			n = parse2 --> 1;
			if(n == 'yes' or 'y//') rtrue;
			if(n == 'no' or 'n//') rfalse;
		}
		PrintMsg(MSG_YES_OR_NO);
	}
];

[ IsorAre p_obj;
	if (p_obj has pluralname || p_obj == player) print "are"; else print "is";
];

[ CObjIs p_obj;
	print (The) p_obj, " ", (isorare) p_obj;
];

[ ItorThem p_obj;
	if (p_obj == player)		{ print (name) player; rtrue; }
	if (p_obj has pluralname)	{ print "them"; rtrue; }
	if (p_obj has animate) {
		if (p_obj has female)	{ print "her"; rtrue; }
		if (p_obj hasnt neuter)	{ print "him"; rtrue; }
	}
	print "it";
];

[ EndOfGame;
	_UpdateScoreOrTime();
	@new_line;
	if(deadflag == GS_QUIT) @quit;
#Iftrue #version_number > 3;
	style bold;
#Endif;
	print "^  *** ";
	if(deadflag == GS_WIN) PrintMsg(MSG_YOU_HAVE_WON);
	else if(deadflag == GS_DEAD) PrintMsg(MSG_YOU_HAVE_DIED);
#Ifdef DeathMessage;
	else if(deadflag >= GS_DEATHMESSAGE) DeathMessage();
#Endif;
	print " ***^^";
#Iftrue #version_number > 3;
	style roman;
#Endif;
#Ifndef NO_SCORE;
	<Score>;
#Endif;
	for(::) {
		PrintMsg(MSG_RESTART_RESTORE_OR_QUIT);
		_ReadPlayerInput(true);
		verb_word = parse-->1;
		if(verb_word == 'restart') @restart;
		if(verb_word == 'restore') <Restore>;
#Ifdef Amusing;
		if(AMUSING_PROVIDED == 0 && deadflag == 2 && verb_word == 'amusing') Amusing();
#Endif;
		if(verb_word == 'quit') @quit;
#IfDef OPTIONAL_FULL_SCORE;
		if(verb_word == 'full') <FullScore>;
#EndIf;
	}
];

! ####################################
!  Parser
! ####################################

#Ifdef OPTIONAL_PRONOUNS;
[ _MatchPronoun p_word _noun;
	! check for pronouns
	! Return:
	! * An object#
	! * 0: No match
	! * 1: Match, error message has been assigned
	switch(p_word) {
		'it': _noun = itobj;
		'him': _noun = himobj;
		'her': _noun = herobj;
		'them': _noun = themobj;
		default: rfalse;
	}
	if(_noun == 0 || TestScope(_noun) == false) {
		parser_error = "I don't know what that pronoun refers to.";
		rtrue;
	} 
	return _noun;
];

[ PronounNotice p_object;
	if(p_object == 0 or player) return;
	if(p_object has pluralname) {
		themobj = p_object;
	} else if(p_object has animate) {
		if(p_object has female) herobj = p_object;
		else if(p_object has neuter) itobj = p_object;
		else himobj = p_object;
	} else itobj = p_object;
	!print "he ", himobj, " she ", herobj, " it ", itobj, "^";
];
#Endif; ! OPTIONAL_PRONOUNS

[ DirectionNumber p_word _i;
	@je p_word 'out' ?_matched_out;
	@je p_word 'in' ?_matched_in;
	@je p_word 'd//' 'down' ?_matched_d;
	@je p_word 'u//' 'up' ?_matched_u;
	@je p_word 'se' 'southeast' ?_matched_se;
	@je p_word 'sw' 'southwest' ?_matched_sw;
	@je p_word 'ne' 'northeast' ?_matched_ne;
	@je p_word 'nw' 'northwest' ?_matched_nw;
	@je p_word 'e//' 'east' ?_matched_e;
	@je p_word 'w//' 'west' ?_matched_w;
	@je p_word 's//' 'south' ?_matched_s;
	@je p_word 'n//' 'north' ?_matched_n;
	
	rfalse;

._matched_out; @inc _i;
._matched_in; @inc _i;
._matched_d; @inc _i;
._matched_u; @inc _i;
._matched_sw; @inc _i;
._matched_se; @inc _i;
._matched_nw; @inc _i;
._matched_ne; @inc _i;
._matched_w; @inc _i;
._matched_e; @inc _i;
._matched_s; @inc _i;
._matched_n; @inc _i;
	return _i;
];

[ MatchObject p_obj p_wordnum _score _addr _len _input_word _w _found _j _prop;
#Ifdef OPTIONAL_REACTIVE_PARSE_NAME;
	if(p_obj has reactive && p_obj provides parse_name) {
#Ifnot;
	if(p_obj provides parse_name) {
#Endif;
		wn = p_wordnum;
		_score = 10 * p_obj.parse_name();
	} else {
		_prop = longnouns;
		if(p_obj.&nouns)
			_prop = nouns;
		_addr = p_obj.&_prop;
		if(_addr) {
			_len = p_obj.#_prop / 2;
!				print "LEN IS ", _len, "^";
			for(_input_word=p_wordnum: _input_word<=num_words: _input_word++) {
				_w = parse-->(_input_word + _input_word - 1);
				_found = false;
				for(_j=0: _j<_len: _j++) {
					if(_addr-->_j == _w) {
						_found = true;
						_score = _score + 10;
						break;
					}
				}
				if(_found == false)
					break;
			}
		}
	}
	if(p_obj hasnt concealed)
		_score = _score + 5;
	if((action_to_be == ##Take or ##TakeAllBut && p_obj notin player) ||
		(action_to_be == ##Drop or ##DropAllBut && p_obj in player))
		_score = _score + 1;
	return _score;
];

[ TryParseToken p_token p_next_token _i _j _obj _input_word _w 
		_score _best_score _the_pointer 
		_which_object _which_objects;
	if(unparsed_start > num_words) rfalse; ! No words left in input
	_w = parse-->(unparsed_start + unparsed_start - 1);
	if(p_token == T_NOUN or T_SECOND) {
		! An object
		_which_object = which_object_noun;
		if(p_token == T_SECOND)
			_which_object = which_object_second;
#Ifdef OPTIONAL_PRONOUNS;
		_i = _MatchPronoun(_w);
		@je _i 1 ?rfalse; ! Got a match, but it didn't work out
		if(_i > 1) {
			_which_object->0 = 1;
			_which_object->1 = _i;
!			_best_obj = _i;
			_best_score = 1;
			jump _done_noun;
		}	
#Endif;
		_the_pointer = unparsed_start;
		while(_the_pointer <= num_words &&
				parse-->(_the_pointer + _the_pointer - 1) == 'the' or 'a//' or 'an')
			_the_pointer++;
#Ifdef DEBUG;
	if(meta) {
		_i = 5; p_next_token = top_object;
	} else {
		_i = 0; p_next_token = scope_objects - 1;
	}
._check_next_object;
		if(meta) _obj = _i; else _obj = scope->_i;
#Ifnot;
	@jz scope_objects ?rfalse; ! No objects in scope so no match
	_i = 0;
	p_next_token = scope_objects - 1;
._check_next_object;
		_obj = scope->_i;
#Endif;

!		for(_i=0: _i<scope_objects: _i++) {
			_score = 0;
!			_obj = scope->_i;
			_score = MatchObject(_obj, _the_pointer);
! REMOVED STUFF HERE
			if(_score > _best_score) {
				_best_score = _score;
				_which_objects = 0;
			}
			if(_score >= _best_score && _which_objects < MAX_WHICH_OBJECTS) {
				_which_objects++;
				_which_object->_which_objects = _obj;
			}
		@inc_chk _i p_next_token ?~_check_next_object;
!		}
		if(_best_score) {
			! We have a list of 1+ objects that match, and all
			! of them have the same score

			if(_which_objects > 1 && _best_score % 10 < 5) {
				! The best-scoring objects are all concealed!
				parser_error = MSG_BE_MORE_SPECIFIC;
				rfalse;
			}
			_which_object->0 = _which_objects;
			! REMOVED DISAMBIG HERE
			_best_score = (_best_score / 10) + _the_pointer - unparsed_start;
._done_noun;
		} else {
			parser_error = MSG_NO_MATCHING_OBJECT;
			if(MatchObject(real_location, _the_pointer))
				parser_error = "You don't need to refer to that.";
		}
!		print "NOUN SCORE: ", _best_score, "^";
	} else if(p_token == T_DIRECTION) {
		_i = DirectionNumber(_w);
		if(_i)
			_best_score = 1;
		direction = direction_properties_array->_i;
	} else if(p_token == T_ALL) {
		if(_w == 'all' or 'everything')
			_best_score = 1;
	} else if(p_token == T_BUT) {
		if(_w == 'but' or 'except')
			_best_score = 1;
	} else if(p_token == T_TOPIC) {
		if(p_next_token == 0) {
			_best_score = num_words - unparsed_start + 1;
		} else {
			for(_input_word=unparsed_start: _input_word<=num_words: _input_word++) {
				_w = parse-->(_input_word + _input_word - 1);
				if(_w == p_next_token) {
					_best_score = _input_word - unparsed_start;
					break;
				}
			}
		}
		if(_best_score) {
			_the_pointer = unparsed_start;
			_j = unparsed_start + _best_score;
			while(_the_pointer < _j &&
					(_obj = parse-->(_the_pointer + _the_pointer - 1)) 
						== 'the' or 'a//' or 'an') {
				_the_pointer++;
			}
			if(_the_pointer < _j) {
				first_topic_word = _obj;
				consult_from = unparsed_start; ! _the_pointer;
				consult_words = _best_score;
			} else {
				! Looked like we had found a topic, but it was just nonsense words
				_best_score = 0;
				parser_error = MSG_NO_TOPIC;
			}
		}
	} else {
		! A specific word
		if(_w == p_token)
			_best_score = 1;
	}
!	print "_best_score for token ", p_token, " is ", _best_score, "^";
	return _best_score;
];

[ TryParse p_token_1 p_token_2 p_token_3 _len;
	noun = 0;
	second = 0;
	which_object_noun->0 = 0;
	which_object_second->0 = 0;
	direction = 0;
	first_topic_word = 0;
	consult_from = 0;
	consult_words = 0;
	_UpdateScope();
	unparsed_start = 2;
	if(p_token_1 == 0) {
		if(num_words == 1)
			rtrue;
	} else {
		_len = TryParseToken(p_token_1, p_token_2);
		if(_len < 1) rfalse;
		if(p_token_2 == 0) {
!			print "left=", (_len + unparsed_start - 1), " right=",num_words,"^";
			if(_len + unparsed_start - 1 == num_words) 
				rtrue;
			else
				rfalse;
		}
		unparsed_start = unparsed_start + _len;
		_len = TryParseToken(p_token_2, p_token_3);
		if(_len < 1) rfalse;
		if(p_token_3 == 0) {
			if(_len + unparsed_start - 1 == num_words) 
				rtrue;
			else
				rfalse;
		}
		unparsed_start = unparsed_start + _len;
		_len = TryParseToken(p_token_3, 0);
		if(_len < 1) rfalse;
		if(_len + unparsed_start - 1 == num_words) 
			rtrue;
		else
			rfalse;
	}
	rfalse;
];

[ Disambiguate p_token _which_object _which_objects _i _best_obj;
	! Picks the first object, if disambiguation fails
	_which_object = which_object_noun;
	if(p_token == T_SECOND)
		_which_object = which_object_second;
	_i = 1; ! an index into which_object
	_which_objects = _which_object->0;
	if(_which_objects > 1) {
		print "Do you mean";
		for(_i = 1: _i <= _which_objects: _i++) {
			if(_i == _which_objects) print " or";
			else if(_i > 1) print ",";
			print " (", _i, ") ", (the) _which_object->_i;
		}
		print "? ";
		_ReadPlayerInput(true, true);
		_i = buffer2->1 - 48;
		if(_i < 1 || _i > _which_objects)
			_i = 1;
!			rtrue;
	}
	if(_which_objects) {
		_best_obj = _which_object->_i;
		if(p_token == T_NOUN)
			noun = _best_obj;
		else
			second = _best_obj;
	}
	rfalse;
];

[ CalcChkSum p_wordnum p_buffer p_parse c i p addr len;
	p = p_parse + 4 * p_wordnum - 2;
	addr = p_buffer + p->3;
	len = p->2;
	if(len) {
!		for(i=0: i<len: i++) {
		i = 0;
		len--;
._nextChar;
			c = DICT_FACTOR * c;
			c = c & $7fff;
			c = c + addr->i;
			c = c & $7fff;
			@inc_chk i len ?~_nextChar;
!		}
	}
	if(c < 1024) c = c - 2000;
	p-->0 = c;
	return c;
];

[ _ReadPlayerInput p_no_prompt p_secondary _result 
		_i _buffer _parse _num_words;
	_buffer = buffer;
	_parse = parse;
	if(p_secondary) {
		_buffer = buffer2;
		_parse = parse2;
	}

	if(p_secondary == false && num_words_enqueued > 0) {
		_i = 1;
		_result = start_words_enqueued;
._copyNextWord;
		_parse-->(_i + _i) = parse-->(_result + _result);
		@inc _result;
		@inc_chk _i num_words_enqueued ?~_copyNextWord;
		num_words = num_words_enqueued;
		_num_words = num_words;
		_parse->1 = num_words;
		num_words_enqueued = 0;
	} else {
		if(p_no_prompt == 0) PrintMsg(MSG_PROMPT);
		_buffer->0 = 78;
		_parse->0 = 19;
		@sread _buffer _parse;
		_num_words = _parse->1;
		if(p_secondary == false) {
			num_words = _num_words;
			num_words_enqueued = 0;
		}
	}
!	for(_i=1: _i<=_num_words: _i++)
!		CalcChkSum(_i, _buffer, _parse);
	_i = 1;
._calcNext;
	_result = CalcChkSum(_i, _buffer, _parse);
!	print "r",_result;
	if(_result == './/' && p_secondary == false) {
		num_words_enqueued = num_words - _i;
		start_words_enqueued = _i + 1;
		num_words = _i - 1;
		_num_words = num_words;
		_parse->1 = num_words;
	}
	@inc_chk _i _num_words ?~_calcNext;
	
];

[ ParseAndPerformAction _i _max _grammar 
		_value _token1 _token2 _token3;
	verb_word = 0;
	meta = false;
		
	if(num_words > 0)
		verb_word = parse-->1;
	else
		"Huh?";

	if(num_words == 1) {
		if(DirectionNumber(verb_word)) {
			verb_word = 'go';
			parse-->3 = parse-->1;
			parse-->4 = parse-->2;
			parse-->1 = verb_word;
			num_words++;
			parse->1 = num_words;
		}
	}
	_i = 0;
._next_verb;
		_token3 = verb_grammar-->_i;
		@jz _token3 ?_no_match;
		@je _token3 verb_word ?_match_verb;
		_i = _i + 2;
		jump _next_verb;
._match_verb;
	_i++;
	_grammar = verb_grammar-->_i;
._no_match;
	if(_grammar == 0) {
		PrintMsg(MSG_UNKNOWN_VERB);
		rfalse;
	}

	parser_error = MSG_DONT_UNDERSTAND;
	_max = _grammar-->0;
	_i = 1;
	if(_grammar-->1 == T_SET_META) {
		meta = 1;
		_i++;
	}
	
	while(_i <= _max) {
		! Read one grammar rule, see if it matches
		_token1 = 0;
		_token2 = 0;
		_token3 = 0;
		action_to_be = _grammar-->_i;
		_i++;
#Iftrue RUNTIME_ERRORS > RTE_MINIMUM;
		if(action_to_be < 0 || action_to_be > 255) {
			_RunTimeError(ERR_PARSE_PATTERN);
			break;
		}
#Endif;
!		print "action = ", action_to_be,"^";
		_value = _grammar-->_i;
		if(_i <= _max && (_value < 0 || _value > 255)) { ! Not an action
			_token1 = _value;
			_i++;
			_value = _grammar-->_i;
			if(_i <= _max && (_value < 0 || _value > 255)) { ! Not an action
				_token2 = _value;
				_i++;
				_value = _grammar-->_i;
				if(_i <= _max && (_value < 0 || _value > 255)) { ! Not an action
					_token3 = _value;
					_i++;
				}
			}
		}
		if(TryParse(_token1, _token2, _token3)) {
			Disambiguate(T_NOUN);
			Disambiguate(T_SECOND);
			<(action_to_be) noun second>;
#Ifdef OPTIONAL_PRONOUNS;
			PronounNotice(noun);
#Endif;
			rtrue;
		}
	}

	PrintMsg(parser_error);

	rfalse; ! Returning false = No action was performed
];

