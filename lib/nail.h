
System_file;

! ####################################
!  Library constants, globals etc
! ####################################

Constant NAIL_MAJOR_VERSION = 1;
Constant NAIL_MINOR_VERSION = 5;
Constant NAIL_PATCH_VERSION = 0; ! Usually 0 (if zero, it is not printed in banner)
!Constant NAIL_VERSION_SUFFIX = "dev"; ! Comment out if none


#Ifndef RUNTIME_ERRORS;
#Ifdef DEBUG;
Constant RUNTIME_ERRORS = 2;
#Ifnot;
Constant RUNTIME_ERRORS = 1;
#Endif;
#Endif;

Default MAX_SCORE 0;


Constant Grammar__Version = 3; ! Should not matter, as we don't use Inform's grammar tables

Constant INDIV_PROP_START 64;
Constant NULL         = $ffff;

! Token values must be in range 256-511 
! (0-255 are verbs, 1000+ are dictionary words, 512-999 reserved for future use)
Constant T_NOUN = 256;
Constant T_SECOND = 257;
Constant T_DIRECTION = 258;
Constant T_ALL = 259;
Constant T_BUT = 260;
Constant T_SET_META 261;
Constant T_TOPIC 262;

Constant RTE_MINIMUM = 0;
Constant RTE_NORMAL  = 1;
Constant RTE_VERBOSE = 2;

Constant WORKFLAG_BIT  $0001;       ! At top level (only), only list objects
                                    ! which have the "workflag" attribute

! location must be the first global to show location name
#Ifdef INITIAL_LOCATION_VALUE;
Global location = INITIAL_LOCATION_VALUE;
#Ifnot;
	#Ifdef OPTIONAL_DARKNESS;
	Global location = thedark;
	#Ifnot;
	Global location = 0;
	#Endif;
#Endif;

#Ifdef NO_SCORE;
Global status_field_1 = NO_SCORE;
#Ifnot;
Global status_field_1 = 0;
#Endif;

Global status_field_2;

#Ifndef NO_SCORE;
Global score;
#Endif;
Global turns = -1;

Global the_time = 0;                ! Current time (in minutes since midnight)
Global time_rate = 1;               ! How often time is updated
Global time_step;                   ! By how much

#Ifndef sys_statusline_flag;
Global sys_statusline_flag = 0;     ! non-zero if status line displays time
#Endif;

Global update_moved;
Global last_player_child = -1;
Global player;
Global real_location;
Global top_object;
Constant GS_QUIT             = -1;
Constant GS_PLAYING          = 0;
Constant GS_DEAD             = 1;
Constant GS_WIN              = 2;
Constant GS_DEATHMESSAGE     = 3;
Global deadflag = GS_PLAYING;

Global also_flag;
Global verb_word;
Global scope_objects;
Global scope_copy_objects;
Global num_words;
Global num_words_enqueued;
Global start_words_enqueued;
Global unparsed_start;
Global action;
Global action_to_be;
Global PrintMsg;
Global meta;
Global run_after_routines_msg;
Global run_after_routines_arg_1;
Global keep_silent;
Global noun;
Global second;
Global direction;
Global debug_flag;
Global scope_modified = true;
Global receive_action;
Global last_light_source;
Global lookmode = 1;
Global no_implicit_actions;
Global parser_error;
Global wn;
Global first_topic_word;
Global consult_from;
Global consult_words;

#Ifdef OPTIONAL_PRONOUNS;
Global itobj = 0;        ! The object which is currently "it"
Global himobj = 0;       ! The object which is currently "him"
Global herobj = 0;       ! The object which is currently "her"
Global themobj = 0;      ! The object which is currently "them"
#Endif;

Global _g_check_take = 0;
Global _g_item = 0;

Global caps_mode;
Constant FORM_CDEF           = 1;
Constant FORM_DEF            = 2;
Constant FORM_INDEF          = 3;

Global notify_mode = true;

Property individual longnouns;
Property nouns;
Property initial;
Property description;
Property cant_go;
Property found_in;
Property time_left;
Property additive time_out $ffff;
Property short_name;
Property additive describe $ffff;
Property additive before $ffff;
Property additive after  $ffff;

Property n_to;  Property s_to;
Property e_to;  Property w_to;
Property ne_to;
Property nw_to;
Property se_to;
Property sw_to;
Property u_to;  Property d_to;
Property in_to; Property out_to;

Array direction_properties_array static -> 0 n_to s_to e_to w_to ne_to nw_to se_to sw_to u_to d_to in_to out_to;

Constant N_TO_CONST = n_to;
Constant OUT_TO_CONST = out_to;

Constant FAKE_N_OBJ = 10001;
Constant FAKE_S_OBJ = 10002;
Constant FAKE_E_OBJ = 10003;
Constant FAKE_W_OBJ = 10004;
Constant FAKE_NE_OBJ = 10005;
Constant FAKE_NW_OBJ = 10006;
Constant FAKE_SE_OBJ = 10007;
Constant FAKE_SW_OBJ = 10008;
Constant FAKE_U_OBJ = 10009;
Constant FAKE_D_OBJ = 10010;
Constant FAKE_IN_OBJ = 10011;
Constant FAKE_OUT_OBJ = 10012;

Property additive each_turn $ffff;

Property door_to            alias n_to;
Property with_key           alias e_to;
Property door_dir           alias w_to;
Property invent             alias se_to;
Property parse_name         alias out_to;
Property daemon             alias time_out;
Property article            alias cant_go;

#Ifdef OPTIONAL_DARKNESS;
Attribute light;
#Endif;
Attribute absent;
Attribute supporter;
Attribute container;
Attribute enterable;
Attribute transparent;
Attribute open;
Attribute openable;
Attribute concealed;
Attribute moved;
Attribute visited alias moved;
Attribute proper;
Attribute scenery;
Attribute static;
Attribute animate;
Attribute clothing;
Attribute worn;
Attribute pluralname;
Attribute female;
Attribute neuter;
Attribute general;
Attribute switchable;
Attribute on;
Attribute door;
Attribute locked;
Attribute lockable;
Attribute workflag;
Attribute reactive;

#IfDef OPTIONAL_SCORED;
Attribute scored;
Default OBJECT_SCORE        4;
Default ROOM_SCORE          5;
#IfDef OPTIONAL_FULL_SCORE;
Global things_score;
Global places_score;
#Endif;
#Endif;

#IfDef OPTIONAL_FULL_SCORE;
#IfDef TASKS_PROVIDED;
Default NUMBER_TASKS        1;
Array  task_done -> NUMBER_TASKS; ! The compiler sets all elements to 0
#Ifndef task_scores;
Array task_scores -> 1;
#Endif;
#Endif;
#Endif;

Default MAX_INPUT_CHARS 78;
Default MAX_INPUT_WORDS 20;

Constant TIMER_TYPE_DAEMON = 10000;
Default MAX_SCOPE 50;
Array scope -> MAX_SCOPE; ! z3 only, so object numbers are single byte
Array scope_copy -> MAX_SCOPE; ! z3 only, so object numbers are single byte
Array buffer->(MAX_INPUT_CHARS + 2);
Array buffer2->(MAX_INPUT_CHARS + 2);
Array _parse->(2 + 4 * MAX_INPUT_WORDS);
Array _parse2->(2 + 4 * MAX_INPUT_WORDS);
Global parse = _parse;
Global parse2 = _parse2;

Default MAX_TIMERS 10; ! Max number of timers and daemons combined that are active at the same time
Array timer_array --> MAX_TIMERS;
Global timers;

Default MAX_FLOATING_OBJECTS 20; ! Max number of objects that have found_in property
Array floating_objects -> MAX_FLOATING_OBJECTS + 1;

Default MAX_WHICH_OBJECTS 10;
Array which_object_noun -> MAX_WHICH_OBJECTS + 1;
Array which_object_second -> MAX_WHICH_OBJECTS + 1;

Global IsARoutine = _IsARoutine_Case1;
Global IsAString = _IsAString_Case1;

Fake_Action Receive;
Fake_Action LetGo;
Fake_Action ThrownAt;
Fake_Action Going;

! Z-code header constants
Constant HDR_ZCODEVERSION  $00;     ! byte
Constant HDR_TERPFLAGS     $01;     ! byte
Constant HDR_GAMERELEASE   $02;     ! word
Constant HDR_HIGHMEMORY    $04;     ! word
Constant HDR_INITIALPC     $06;     ! word
Constant HDR_DICTIONARY    $08;     ! word
Constant HDR_OBJECTS       $0A;     ! word
Constant HDR_GLOBALS       $0C;     ! word
Constant HDR_STATICMEMORY  $0E;     ! word
Constant HDR_GAMEFLAGS     $10;     ! word
Constant HDR_GAMESERIAL    $12;     ! six ASCII characters
Constant HDR_ABBREVIATIONS $18;     ! word
Constant HDR_FILELENGTH    $1A;     ! word
Constant HDR_CHECKSUM      $1C;     ! word
Constant HDR_TERPNUMBER    $1E;     ! byte
Constant HDR_TERPVERSION   $1F;     ! byte
Constant HDR_SCREENHLINES  $20;     ! byte
Constant HDR_SCREENWCHARS  $21;     ! byte
Constant HDR_SCREENWUNITS  $22;     ! word
Constant HDR_SCREENHUNITS  $24;     ! word
Constant HDR_FONTWUNITS    $26;     ! byte
Constant HDR_FONTHUNITS    $27;     ! byte
Constant HDR_ROUTINEOFFSET $28;     ! word
Constant HDR_STRINGOFFSET  $2A;     ! word
Constant HDR_BGCOLOUR      $2C;     ! byte
Constant HDR_FGCOLOUR      $2D;     ! byte
Constant HDR_TERMCHARS     $2E;     ! word
Constant HDR_PIXELSTO3     $30;     ! word
Constant HDR_TERPSTANDARD  $32;     ! two bytes
Constant HDR_ALPHABET      $34;     ! word
Constant HDR_EXTENSION     $36;     ! word
Constant HDR_UNUSED        $38;     ! two words
Constant HDR_INFORMVERSION $3C;     ! four ASCII characters

#Ifdef OPTIONAL_DARKNESS;
Object thedark "Darkness"
	with
		initial 0,
		description "It is pitch dark here!",
 		short_name 0;
#Endif;

! ####################################
!  main
! ####################################

[ main _i _j _score;
	top_object = #largest_object-255;
	player = selfobj;
	PrintMsg = _PrintMsg;
	_score = 0;

! Pick the correct case for custom logic in RunRoutines.
! 1: #strings_offset > 0 (DEFAULT)
! 2: #code_offset > 0 && #strings_offset < 0
! 3: #code_offset < 0 && #strings_offset < 0 (CAN'T HAPPEN)
	if(#strings_offset < 0) {
!		_puny_zregion_case = _PunyZRegionCase2;
		IsARoutine = _IsARoutine_Case2;
		IsAString = _IsAString_Case2;
	}
	
	_InitObjects();
	_j = Initialise();
	objectloop (_i in player) give _i moved ~concealed;
	update_moved = false;
	if(_j ~= 2)
		Banner();
	
	if(parent(player) == 0) { _i = location; location = 0; PlayerTo(_i); }
	
	turns = 0;
	while(deadflag == GS_PLAYING) {
		_UpdateScoreOrTime();
#Ifndef NO_SCORE;
		_score = score;
#Endif;
._newInput;
		_ReadPlayerInput();
		if(buffer->1 == '*') {
			num_words_enqueued = 0;
			PrintMsg(MSG_COMMENT_ACCEPTED);
			jump _newInput;
		}

		if(ParseAndPerformAction() && meta == false) {
			EndTurnSequence();
		}

#Ifdef AfterLife;
		if(deadflag ~= GS_PLAYING or GS_WIN or GS_QUIT) {
			! we died somehow, use entry routine to give
			! a chance of resurrection
			AfterLife();
		}
#Endif;

#Ifndef NO_SCORE;
		if(_score ~= score && notify_mode == true) {
			PrintMsg(MSG_PARSER_NEW_SCORE, _score);
		}
#Endif;

	}
	EndOfGame();
];

! ####################################
!  Messages
! ####################################

Constant ERR_PARSE_PATTERN 1;
Constant ERR_BROKEN_DOOR 2;
Constant ERR_TOO_MANY_FLOATING 3;
Constant ERR_SCOPE_FULL 4;
Constant ERR_NOT_DIR_PROP 5;
Constant ERR_UNKNOWN_MSG 6;
Constant ERR_BUFFER_OVERRUN 7;

[_RunTimeError p_err p_obj _parent;
	print "^[NAIL error: ";
	if(IsAString(p_err))
		print (string) p_err;
	else {
		print p_err;
#Iftrue RUNTIME_ERRORS == RTE_VERBOSE;
		print " - ";
		switch(p_err) {
		ERR_PARSE_PATTERN:
			print "Broken parse table";
		ERR_BROKEN_DOOR:
			print "Broken door";
		ERR_TOO_MANY_FLOATING:
			print "Too many floating objects";
		ERR_SCOPE_FULL:
			print "Scope full";
		ERR_NOT_DIR_PROP:
			print "DirPropToFakeObj was called with a value that is not a direction property.";
		ERR_UNKNOWN_MSG:
			print "PrintMsg was called with an unknown value.";
		ERR_BUFFER_OVERRUN:
			print "Goto printed an object name longer than the buffer - Increase GOTOSUB_BUFFER_SIZE.";
		default:
			print "Unknown error";
		}
#Endif;
	}
	print "]^";
#Iftrue RUNTIME_ERRORS == RTE_VERBOSE;
	if(p_obj ofclass object) {
		_parent = parent(p_obj);
		print "Offending object: ", (the) p_obj, " (", p_obj, ") in ", (name) _parent, " (", _parent, ")^";
	}
#Ifnot;
	_parent = p_obj; ! Avoid compiler warning
#Endif;
	rtrue;
];

! ####################################
!  Library routines
! ####################################

#Ifndef DebugParseNameObject;
[ DebugParseNameObject p_obj;
	p_obj = 0;
	rfalse;
];
#Endif;

#Ifdef IsARoom;
[ _RoomLike p_obj _verdict _return_code;
#Ifnot;
[ _RoomLike p_obj _verdict;
#Endif;

	! Return true if p_obj seems to be a room
	if(p_obj > 4 && p_obj <= top_object && p_obj in nothing
			&& p_obj provides description
			&& (~~(p_obj provides describe or found_in))
			&& (~~DebugParseNameObject(p_obj))) {
		if(p_obj has supporter or container or transparent
				or concealed or scenery or static or animate or clothing
				or pluralname or switchable or door or lockable)
			jump _decided;
#Ifdef OPTIONAL_DARKNESS;
		if(p_obj == thedark) jump _decided;
#Endif;
		_verdict = true;
	}
._decided;
#Ifdef IsARoom;
	_return_code = IsARoom(p_obj, _verdict);
	if(_return_code)
		_verdict = 2 - _return_code;
#Endif;
	return _verdict;
];

[ _ObjectLike p_obj;
	if(p_obj > 4 && p_obj <= top_object && p_obj notin Class && _RoomLike(p_obj) == false) {
#Ifdef OPTIONAL_DARKNESS;
		if(p_obj == thedark) rfalse;
#Endif;	
		rtrue;
	}
	rfalse;
];

[ NextWord _i _j;
	if (wn <= 0 || wn > parse->1) { wn++; rfalse; }
	_i = wn + wn - 1; wn++;
	_j = parse-->_i;
!	if (_j == ' ,//') _j = comma_word;
!	if (_j == ' .//') _j = THEN1__WD;
	return _j;
];

[ NextWordStopped;
	if (wn > parse->1) { wn++; return -1; }
	return NextWord();
];

[ TryNumber p_wordnum _i _j _num _len _d _tot _digit;
	!  Takes word number p_wordnum and tries to parse it as an
	! unsigned decimal number, returning
	!
	!  -1000				if it is not a number
	!  the number		    if it has between 1 and 4 digits
	!  10000				if it has 5 or more digits.

	_i = p_wordnum*4+1; _j = parse->_i; _num = _j+buffer; _len = parse->(_i-1);

	! this uses Horner's algorithm: 2421 = 10*(10*(10*(2)+4)+2)+1
	for (_i=0: _i<_len: _i++) {
		_digit = _num->_i;
		if(_digit < '0' || _digit > '9') jump _trynumber_baddigit;
		_d = _digit - '0';
		if(_len <=4) _tot = _tot*10 + _d;
	}
   	if (_len > 4) return 10000;
	return _tot;
._trynumber_baddigit;
	return -1000;
];

[ WordAddress p_wordnum _pointer; ! Absolute addr of ' wordnum' string in buffer
#Iftrue #version_number > 4;
    @log_shift p_wordnum 2 -> _pointer; ! Multiply by 4
#Ifnot;
    _pointer = 4 * p_wordnum;
#Endif;
	_pointer++;
	return buffer + parse->_pointer;
];

[ WordLength p_wordnum _pointer; ! Length of ' wordnum' string in buffer
#Iftrue #version_number > 4;
    @log_shift p_wordnum 2 -> _pointer; ! Multiply by 4
#Ifnot;
    _pointer = 4 * p_wordnum;
#Endif;
	return parse->_pointer;
];

[ WordValue p_wordnum;	  ! Dictionary value of ' wordnum' string in buffer
	return parse-->(p_wordnum + p_wordnum - 1);
];

[ EndTurnSequence;
	turns++;
#Ifndef STATUSLINE_SCORE;
#Ifndef STATUSLINE_TIME;
	if (sys_statusline_flag) {
#Endif;
		if (time_rate >= 0) the_time=the_time+time_rate;
		else {
			time_step--;
			if (time_step == 0) {
				the_time++;
				time_step = -time_rate;
			}
		}
		the_time = the_time % 1440;
#Ifndef STATUSLINE_TIME;
	}
#Endif;
#Endif;
	@jz deadflag ?~rtrue; ! Return if game is over
	RunTimersAndDaemons(); @jz deadflag ?~rtrue; ! Return if game is over
	RunEachTurn(); @jz deadflag ?~rtrue; ! Return if game is over
	
#Ifdef TimePasses;
	TimePasses();
#Endif;
#Ifdef OPTIONAL_DARKNESS;
	_UpdateDarkness();
#Endif;

	if(update_moved || child(player) ~= last_player_child or 0) {
		_NoteObjectAcquisitions();
		update_moved = false;
		last_player_child = child(player);
	}

];

[ _NoteObjectAcquisitions _i;
	objectloop(_i in player) {
		if(_i hasnt moved) {
			give _i moved;
#IfDef OPTIONAL_SCORED;
			if(_i has scored) {
				score = score + OBJECT_SCORE;
#IfDef OPTIONAL_FULL_SCORE;
				things_score = things_score + OBJECT_SCORE;
#EndIf;
			}
#EndIf;
		}
	}
];

[ Banner _i;
	new_line;
#Ifdef Story;
	#Iftrue #version_number > 3;
		style bold;
	#Endif;
		print (string) Story;
	#Iftrue #version_number > 3;
		style roman;
	#Endif;
	#Ifdef Headline;
		print (string) Headline;
	#Ifnot;
		new_line;
	#Endif;
#Endif;
	print "Release ", (0-->1) & $03ff, " / Serial number ";
	for (_i = 18:_i < 24: _i++) print (char) 0->_i;
	print " / Inform v";
	inversion;
	print " NAIL v", NAIL_MAJOR_VERSION, (char) '.', NAIL_MINOR_VERSION;
	if(NAIL_PATCH_VERSION)
		print (char) '.', NAIL_PATCH_VERSION;
#Ifdef NAIL_VERSION_SUFFIX;
	print (string) NAIL_VERSION_SUFFIX;
#EndIf;
	print (char) ' ';
#IfDef STRICT_MODE;
	#Iftrue #version_number > 4;
	print (char) 'S';
	#Endif;
#EndIf;
#IfDef DEBUG;
	print (char) 'D';
#EndIf;
#IfTrue RUNTIME_ERRORS > 0;
	print (char) 'R';
#EndIf;
	new_line;
];

[ _UpdateScoreOrTime;
#Ifdef STATUSLINE_TIME;
	status_field_1 = the_time/60;
	status_field_2 = the_time%60;
#Ifnot;
	#Ifdef STATUSLINE_SCORE;
	#Ifndef NO_SCORE;
		status_field_1 = score;
	#Endif;
		status_field_2 = turns;
	#Ifnot;
		if (sys_statusline_flag == 0) {
			#Ifndef NO_SCORE;
				status_field_1 = score;
			#Endif;
			status_field_2 = turns;
		} else {
			status_field_1 = the_time/60;
			status_field_2 = the_time%60;
		}
	#Endif;
#Endif;
];

[ SetTime p_time p_step;
	the_time = p_time;
	time_rate = p_step;
	time_step = 0;
	if(p_step < 0) time_step = -p_step;
];

[ CommonAncestor p_o1 p_o2 _i _j;
	! Find the nearest object indirectly containing o1 and o2,
	! or return 0 if there is no common ancestor.
	_i = p_o1;
	while (_i) {
		_j = p_o2;
		while (_j) {
			if (_j == _i) return _i;
			_j = parent(_j);
		}
		_i = parent(_i);
	}
	return 0;
];

[ IndirectlyContains p_o1 p_o2;
	! Does o1 indirectly contain o2?  (Same as testing if o1 is one of the ancestors of o2.)
	@jz p_o2 ?rfalse;
._recheck;
	@je p_o1 p_o2 ?rtrue;
!	if (p_o1 == p_o2) rtrue;
	p_o2 = parent(p_o2);
	@jz p_o2 ?~_recheck;
	rfalse;
];

[ _IsARoutine_Case1 p_value;
	! Decide if a value is a routine address, faster than using ofclass
	! Case 1, code_offset > 0 && strings_offset > 0
	@jl p_value (#strings_offset) ?~rfalse;
	@jl p_value (#code_offset) ?~rtrue;
	rfalse;
];

[ _IsARoutine_Case2 p_value;
	! Decide if a value is a routine address, faster than using ofclass
	! Case 2, code_offset > 0 && strings_offset < 0
	@jl p_value (#code_offset) ?~rtrue;
	@jl p_value (#strings_offset) ?rtrue;
	rfalse;
];

[ _IsAString_Case1 p_value;
	! Decide if a value is a string address, faster than using ofclass
	! Case 1, code_offset > 0 && strings_offset > 0
	@jl p_value (#strings_offset) ?~rtrue;
	@jl p_value (-1) ?rtrue;
	rfalse;
];

[ _IsAString_Case2 p_value;
	! Decide if a value is a string address, faster than using ofclass
	! Case 2, code_offset > 0 && strings_offset < 0
	@jl p_value (#strings_offset) ?rfalse;
	@jl p_value (-1) ?rtrue;
	rfalse;
];


![ RunRoutines p_obj p_prop _sw _result;
!	if(p_obj provides p_prop) {
!		_sw = sw__var; sw__var = action;
!		_result = p_obj.p_prop();
!		sw__var = _sw;
!	}
!	return _result;
!];

[ RunRoutines p_obj p_prop p_switch _sw__var _self _address 
		_len _i _value _result;
#Ifdef OPTIONAL_DARKNESS;
	if(p_obj == thedark && p_prop ~= initial or short_name or description)
		p_obj = real_location;
#Endif;
	_address = p_obj.&p_prop;
	if (p_prop < INDIV_PROP_START || _address ~= 0) {
		_sw__var = sw__var;
		if(p_switch == 0) sw__var = action; else sw__var = p_switch;
		_self = self; self = p_obj;
!		p_switch = p_obj.p_prop();
		if(_address == 0) { _value = p_obj.p_prop; jump _process_value; }
		_len = p_obj.#p_prop;
#Iftrue #version_number > 4;
		@log_shift _len (-1) -> _len; ! Divide by 2
#Ifnot;
		_len = _len / 2;
#Endif;
		@dec _len;
._get_next_value;
		_value = _address-->_i;
._process_value;
		@je _value 0 (-1) ?_isZero;
		if(IsARoutine(_value)) jump _isRoutine;
		if(IsAString(_value)) jump _isString;
		jump _isConstant;

._isRoutine;
			@call _value -> _result;
			@jz _result ?_next;
			jump _done;
._isString;
			print (string) _value, "^";
			_result = true;
			jump _done;
._isZero;
			_value = 0;
._isConstant;
			_result = _value;
			jump _done;
._next;
		@inc_chk _i _len ?~_get_next_value;
._done;
		self = _self;
		sw__var = _sw__var;
	}
	return _result;
];


[ PrintOrRun p_obj p_prop p_no_string_newline _val;
	if (p_obj.#p_prop > WORDSIZE || IsARoutine((_val = p_obj.p_prop)))
		return RunRoutines(p_obj, p_prop);
	if(IsAString(_val)) {
		print (string) _val;
		if(p_no_string_newline == 0) new_line;
		rtrue;
	}
	return _val;
];

[ _RunReact p_property p_break _i _obj _max;

	! Loop over the scope to find possible react_before/after routines
	! to run in each object. Return:
	! * false if no routines were found
	! * true if routines were found, p_break was true, and a routine didn't return false
	! * Otherwise:
	!	* if OPTIONAL_MANUAL_SCOPE_BOOST is defined, return 2
	!	* if not, return false

	if(scope_copy_objects == 0) rfalse;
	_max = scope_copy_objects - 1;
._RunReactNext;
	_obj = scope_copy->_i;
	if (_obj has reactive && _obj.&p_property ~= 0 && ( _obj.#p_property > 2 || _obj.p_property ~= NULL or 0)) {
#Ifdef DEBUG;
!#Iftrue #version_number < 5;
		if(debug_flag & 1) print "[ ~", (name) _obj, "~.",(property) p_property,"() ]^";
!#Endif;
#Endif;
		if(RunRoutines(_obj, p_property) && p_break) {
			rtrue;
		}
		@jz deadflag ?~rtrue; ! Return if game is over
	}
	@inc_chk _i _max ?~_RunReactNext;
	rtrue;
];

[ RunEachTurn;
	! Run all each_turn routines for location and all objects in scope.

!	GetScopeCopy(player, EACH_TURN_REASON); ! later used by _RunReact
	GetScopeCopy(); ! later used by _RunReact

	if(location has reactive && location.&each_turn ~= 0) {
#Ifdef DEBUG;
		if(debug_flag & 1) print "[ ~", (name) location, "~.each_turn() ]^";
#Endif;
		RunRoutines(location, each_turn);
		@jz deadflag ?~rtrue; ! Return if game is over
	}

	_RunReact(each_turn);
];

[ BeforeRoutines;
	if(real_location == 0) rfalse;

#IfDef GamePreRoutine;
#IfDef DEBUG;
	if(debug_flag & 1) print "[ GamePreRoutine() ]^";
#EndIf;
	if(GamePreRoutine()) rtrue;
#EndIf;

	if(real_location.&before) {
#Ifdef DEBUG;
		if(debug_flag & 1) print "[ ~", (name) real_location, "~.before() ]^";
#Endif;
		if(RunRoutines(real_location, before)) rtrue;
	}
	if(noun && noun.&before && noun ~= real_location) {
#Ifdef DEBUG;
		if(debug_flag & 1) print "[ ~", (name) noun, "~.before() ]^";
#Endif;
		if(RunRoutines(noun, before)) rtrue;
	}
	rfalse;
];

[ AfterRoutines;
	if(real_location == 0) rfalse;

	if(real_location.&after) {
#Ifdef DEBUG;
		if(debug_flag & 1) print "[ ~", (name) real_location, "~.after() ]^";
#Endif;
		if(RunRoutines(real_location, after)) rtrue;
	}
	if(noun && noun.&after && noun ~= real_location) {
#Ifdef DEBUG;
		if(debug_flag & 1) print "[ ~", (name) noun, "~.after() ]^";
#Endif;
		if(RunRoutines(noun, after)) rtrue;
	}
#IfDef GamePostRoutine;
#IfDef DEBUG;
	if(debug_flag & 1) print "[ GamePostRoutine() ]^";
#EndIf;
	if(GamePostRoutine()) rtrue;
#EndIf;
	rfalse;
];

#Ifdef OPTIONAL_DARKNESS;
[ _UpdateDarkness p_silent _ceil _old_darkness _darkness;
!	print "Entering _UpdateDarkness^";
	if(location == thedark) _old_darkness = true;
	_ceil = real_location; !ScopeCeiling(player);
	if(_ceil hasnt light) {
		if((last_light_source == 0 || last_light_source hasnt light ||
					parent(last_light_source) ~= player or _ceil) &&
				_LookForLightInObj(_ceil) == false) {
!			print "Decided it's dark!^";
			_darkness = true;
			last_light_source = 0;
		}
	}
	if(_darkness ~= _old_darkness) scope_modified = true;
	if(_darkness) {
		if(_old_darkness == false && p_silent == false) PrintMsg(MSG_NOW_DARK);
		location = thedark;
	} else {
		location = real_location;
		if(_old_darkness && p_silent == false) {
!			new_line;
			<Look>;
		}
	}
];

[ _LookForLightInObj p_obj _o;
!	if(p_obj has light) rtrue;
	@test_attr p_obj light ?rtrue;
	objectloop(_o in p_obj) {
		if(_o has light) { last_light_source = _o; rtrue; }
		if(_o has transparent or supporter || 
				(_o has container && _o has open))
			if(_LookForLightInObj(_o)) rtrue;
	}
	rfalse;
];
#Endif;

[ Superparent p_obj _parent;
	while(true) {
		_parent = parent(p_obj);
		if(_parent == 0)
			return p_obj;
		p_obj = _parent;
	}
];

[ PlayerTo p_loc p_flag _old_loc _old_real_loc _old_lookmode;
	_old_loc = location;
	_old_real_loc = real_location;
	move player to p_loc;
	real_location = superparent(p_loc);
	location = real_location;
	MoveFloatingObjects(); ! Also sets scope_modified = true;
#Ifdef OPTIONAL_DARKNESS;
	_UpdateDarkness(true);
#Endif;
!	if(p_flag == 0) {
!		PrintOrRun(real_location, initial);
!		<<Look>>;
!	}

#Ifdef NewRoom;
#Ifdef OPTIONAL_DARKNESS;
		if(location ~= thedark)
			NewRoom();
#Ifnot;
		NewRoom();
#Endif;
#Endif;

#Ifdef OPTIONAL_DARKNESS;
#Ifdef DarkToDark;
	if(_old_real_loc ~= real_location && location == thedark && _old_loc == thedark) {
		! we have moved between dark rooms
		! give entry point a chance to react
		DarkToDark();
	}
#Endif;
#Endif;

	PrintOrRun(real_location, initial);
	if(p_flag~=true && deadflag == GS_PLAYING) {
		_old_lookmode = lookmode;
		if(p_flag==false)
			lookmode = 2;
		Look();
		lookmode = _old_lookmode;
	}
];

[ LocateWordValue p_arr p_length p_value _i _val;
	@jl p_length 1 ?_not_found;
	p_length--;
._check_next_pos;
	_val = p_arr --> _i;
	@je _val p_value ?_found;
	@inc_chk _i p_length ?~_check_next_pos;
._not_found;
	return -1;
._found;
	return _i;
];

[ StartTimer p_obj p_time;
	if(p_obj > 0)
		p_obj.time_left = p_time;
	! Check if already running
	if(timers > 0 && LocateWordValue(timer_array, timers, p_obj) >= 0)
		rtrue;
	timer_array-->timers = p_obj;
	timers++;
	rtrue;
];

[ StopTimer p_obj _pos;
	@jz timers ?rtrue;
	! Find object in timer array
	_pos = LocateWordValue(timer_array, timers, p_obj);
	if(_pos < 0) rtrue;
	timers--;
	timer_array --> _pos = timer_array --> timers;
	timer_array --> timers = 0;
	rtrue;
];

[ StartDaemon p_obj;
	StartTimer(-p_obj);
];

[ StopDaemon p_obj;
	StopTimer(-p_obj);
];

[ RunTimersAndDaemons _i _obj _val _count;
	if(timers == 0) rtrue;
	_count = timers - 1;
._run_next_timer;
	_obj = timer_array --> _i;

#IfDef DEBUG;
		if(debug_flag & 4) {
			print "[ Running ";
			if(_obj > 0) {
				print "timer ", (DebugParameter) _obj;
				if(_obj.time_left > 0)
					print " with time_left = ", _obj.time_left;
				else
					print ": time_out";
			} else
				print "daemon ", (DebugParameter) (-_obj);
			print "]^";
		}
#EndIf;

	if(_obj > 0) {
		_obj.time_left--;
		_val = _obj.time_left;
		@jz _val ?~_dont_run;
		StopTimer(_obj);
		_i--;
		_count--;
	} else
		_obj =  -_obj;
	_obj.daemon();
	@jz deadflag ?~rtrue; ! Return if game is over
._dont_run;
	@inc_chk _i _count ?~_run_next_timer;
];

[ _InitObjects _i _k _v;
	_i = 5; ! Lowest object# (Compiler creates Class, Object, String, Routine)
.objloop;
		@get_prop_addr _i found_in -> _v;
		@jz _v ?not_floating;
#IfTrue RUNTIME_ERRORS > RTE_MINIMUM;
			if(_k >= MAX_FLOATING_OBJECTS) {
				_RunTimeError(ERR_TOO_MANY_FLOATING);
				rtrue;
			}
#EndIf;
			floating_objects->(_k++) = _i;
.not_floating;
	@inc_chk _i top_object ?~objloop;
	return;
];


[ MoveFloatingObjects _i _j _o _len _obj _self;
	_i--;
._next_floating;
		_i++;
		_obj = floating_objects->_i;
		if(_obj == 0)
			jump _done_floating;
!		if(parent(_obj) ~= 0 && IndirectlyContains(player, _obj))
!			jump _next_floating;
		if(_obj has absent)
			jump _isnt_present;
		_len = _obj.#found_in;
		if(_len == 2) {
			_j = _obj.found_in;
			if(_j > top_object || _j < -1) {
				_self = self; self = _obj;
				@call _j -> _j;
				self = _self;
				@jz _j ?_isnt_present;
				jump _is_present;
			}
			@je _j (-1) ?_isnt_present;
		}
		_j = _obj.&found_in;
#Iftrue #version_number > 4;
		@log_shift _len (-1) -> _len; ! Divide by 2
#Ifnot;
		_len = _len / 2;
#Endif;
		_len = _len - 1;
._check_next_value;
			_o = _j-->_len;
			if(_o in Class) {
				if(location ofclass _o)
					jump _is_present;
			} else if(_o == location || _o in location)
				jump _is_present;
		@dec_chk _len 0 ?~_check_next_value;
._isnt_present;
		remove _obj;
		jump _next_floating;
._is_present;
		if(_obj notin location)
			move _obj to location;
		jump _next_floating;

._done_floating;
	! It's not certain that scope has been modified, but PlayerTo relies on it
	! being set.
	scope_modified = true;
];

! ####################################
!  Object printing routines
! ####################################


[ PrintShortName o;
	if(caps_mode == 2) 
		caps_mode = true;
	else 
		caps_mode = false;
	if (o == 0) { print "nothing"; rtrue; }
	if(metaclass(O) ~= Object) { print "<Not an object>"; rtrue; }
!	switch (metaclass(o)) {
!	  Routine:  print "<routine ", o, ">"; rtrue;
!	  String:   print "<string ~", (string) o, "~>"; rtrue;
!	  nothing:  print "<illegal object number ", o, ">"; rtrue;
!	}
	if (o.short_name ~= 0 && PrintOrRun(o, short_name, true) ~= 0) rtrue;
	print (object) o;
];

[ _PrintObjName p_obj p_form;
	caps_mode = false;
	if(p_form == FORM_CDEF)
		caps_mode = 2;
	if(p_obj hasnt proper) {
		if(p_form == FORM_CDEF) {
			print "The ";
		} else if(p_form == FORM_DEF) {
			print "the ";
		} else if(p_form == FORM_INDEF) {
			if(p_obj.&article) {
				PrintOrRun(p_obj, article, true);
				print " ";
			}
			else if(p_obj has pluralname)
				print "some ";
			else
				print "a ";
		}
	}
	PrintShortName(p_obj);
];

[ CDefArt p_obj _result;
	_result = _PrintObjName(p_obj, FORM_CDEF);
];

[ DefArt p_obj _result;
	_result = _PrintObjName(p_obj, FORM_DEF);
];

[ IndefArt p_obj _result;
	_result = _PrintObjName(p_obj, FORM_INDEF);
];

[ _PrintContentsPrintAnObj p_obj p_style;
	if(PrintOrRun(p_obj, invent, true))
		rtrue;
	print (a) p_obj;
#Ifdef OPTIONAL_DARKNESS;
	if(p_obj has light or worn) {
#Ifnot;
	if(p_obj has worn) {
#Endif;
		print " (";
#Ifdef OPTIONAL_DARKNESS;
		if(p_obj has worn) {print "worn"; if(p_obj has light) print ", "; }
		if(p_obj has light) print "providing light";
#Ifnot;
		if(p_obj has worn) {print "worn"; }
#Endif;
		print ")";
	}
	if(p_obj has container) {
		print " (";
		if(p_obj has open or transparent) {
			if(p_obj has openable) {
				if(p_obj has open) print "open, "; else print "closed, ";
			}
			if(PrintContents("containing ", p_obj) == 0) print "empty";
		} else 
			print "closed";
		print ")";
	} else if(p_obj has supporter)
		if(PrintContents(" (holding ", p_obj)) print ")";
	p_style = 0; ! Avoid warning
];

[ PrintContents p_first_text p_base_obj p_style _obj _printed _queue;
	_obj = child(p_base_obj);
	while(_obj) {
		if(_obj ~= player && _obj hasnt scenery or concealed && 
				((p_style & WORKFLAG_BIT == 0) || _obj has workflag)) {
			if(_printed == _queue) {
				if(IsAString(p_first_text))
					print (string) p_first_text; 
				else if(IsARoutine(p_first_text))
					p_first_text(p_base_obj); 
			}
			if(_queue) {		
				if(_printed) print ", ";
				_PrintContentsPrintAnObj(_queue, p_style);
				_printed++;
			}
			_queue = _obj;
		}
		_obj = sibling(_obj);	
	}
	if(_queue) {
		if(_printed)
			print " and ";
		_PrintContentsPrintAnObj(_queue, p_style);
		_printed++;
	}
	return _printed;
];

! ####################################
!  Scope routines
! ####################################

[_PutInScope p_obj p_risk_duplicate _i;
#IfDef DEBUG_SCOPE;
#IfDef DEBUG;
	if(p_obj) print "_PutInScope adding ",(object) p_obj," (", p_obj,") to scope. Action = ", (DebugAction) action, "^";
#IfNot;
	if(p_obj) print "_PutInScope adding ",(object) p_obj," (", p_obj,") to scope. Action = ", action, "^";
#EndIf;
#EndIf;
	if(p_risk_duplicate == 0 && scope_objects > 0) {
		_i = scope_objects - 1;
._check_next_obj;
		if(scope->_i == p_obj) rfalse; ! All well, obj was already in scope
		@dec_chk _i 0 ?~_check_next_obj;
	}
	! Check if there is room
	if(scope_objects >= MAX_SCOPE) {
#IfTrue RUNTIME_ERRORS > RTE_MINIMUM;
		_RunTimeError(ERR_SCOPE_FULL);
#EndIf;
		rtrue; ! Error, obj could not be put in scope
	}
	! Add it
	scope->scope_objects = p_obj;
	scope_objects++;
	rfalse; ! All well
];

Constant PlaceInScope = _PutInScope;

[ ScopeWithin p_obj _child;
	! DM: ScopeWithin(obj)
	! Used in "scope routines" (only) when scope_stage is set to 2 (only).
	! Places the contents of obj in scope for the token currently being
	! parsed, and applies the rules of scope recursively so that contents of
	! see-through objects are also in scope, as is anything added to scope.
	!
	! Note that p_obj is NOT added to the scope, only its contents.
	!
	! No return value

	! Get the first child. If no children, return
	@get_child p_obj -> _child ?~rtrue;

	! add the child (will also add all siblings)
	_SearchScope(_child);
];

[ _SearchScope p_obj p_risk_duplicates;
	while(p_obj) {
		_PutInScope(p_obj, p_risk_duplicates);
		if(p_obj has supporter or transparent || 
				(p_obj has container && p_obj has open))
			_SearchScope(child(p_obj), p_risk_duplicates);
		p_obj = sibling(p_obj);
	}
];

#IfDef InScope;
[ _UpdateScope _initial_scope_objects _risk_duplicates _can_skip 
		_i _j _k _m _obj _obj_2;
#IfNot;
[ _UpdateScope _initial_scope_objects _risk_duplicates
!		_i _j _k _m _obj _obj_2
	;
#EndIf;

	if(scope_modified == false) {
#IfDef InScope;
		_can_skip = true;
#IfNot;
		rtrue;
#EndIf;
	}
	scope_modified = false;
	_initial_scope_objects = scope_objects; 
	scope_objects = 0;
	_risk_duplicates = 1;

#Ifdef InScope;
	! give entry routine a chance to override
	_i = InScope();
	if(_i ~= 0 || scope_objects > 0) {
		scope_modified = true; ! Force a hard scope update next call
		if(_i) jump _done_updating_scope;
		_risk_duplicates = 0;
	} else if(_can_skip) {
		! Neither scope routine or InScope have modified scope
		scope_objects = _initial_scope_objects;
		rtrue;
	}
#Endif;

#Ifdef OPTIONAL_DARKNESS;
	if(location == thedark) {
		! only the player's possessions and whatever is in the dark are in scope
		_PutInScope(player, _risk_duplicates);
		_SearchScope(child(player), _risk_duplicates);
	} else
		_SearchScope(child(location), _risk_duplicates);
#Ifnot;
	_SearchScope(child(location), _risk_duplicates);
#Endif;

._done_updating_scope;

! REMOVED SORTING CONCEALED here

	rtrue;
];

#Iftrue #version_number > 4;
[GetScopeCopy _i;
#Ifnot;
[GetScopeCopy _i _max;
#Endif;

!	_UpdateScope(p_actor, p_reason);
	_UpdateScope();

!	if(scope_copy_actor ~= p_actor) {
#Iftrue #version_number > 4;
		@log_shift scope_objects 1 -> _i; ! _i = scope_objects * 2
		@copy_table scope scope_copy _i;
#Ifnot;
		if(scope_objects) {
			_max = scope_objects - 1;
._copy_next_entry;
			scope_copy->_i = scope->_i;
			@inc_chk _i _max ?~_copy_next_entry;
		}
#Endif;
!		scope_copy_actor = p_actor;
!	}
	scope_copy_objects = scope_objects;
	return scope_copy_objects;
];

[ _FindBarrier p_ancestor p_obj p_dontprint;
	while (p_obj ~= p_ancestor) {
		if (_g_check_take && p_obj hasnt container && p_obj hasnt supporter) {
						! We're going to return true here, we just need to write the correct message
						! But if we don't need to print anything, just return now
						if (p_dontprint) rtrue;

			if (p_obj has animate) {
				PrintMsg(MSG_TAKE_BELONGS, _g_item, p_obj); rtrue;
			}
			if (p_obj has transparent) {
				PrintMsg(MSG_TAKE_PART_OF, _g_item, p_obj); rtrue;
			}
			PrintMsg(MSG_TAKE_NOT_AVAILABLE); rtrue;
		}
		if(p_obj has container && p_obj hasnt open) {
			if(p_dontprint == false) PrintMsg(MSG_OBJ_NOT_OPEN, p_obj);
			rtrue;
		}
		p_obj = parent(p_obj);
	}
	rfalse;
];

[ ObjectIsUntouchable p_item p_dontprint p_checktake _ancestor;
	! DM: ObjectIsUntouchable(obj,flag)
	! Determines whether any solid barrier, that is, any container that is
	! not open, lies between the player and obj. If flag is true, this
	! routine never prints anything; otherwise it prints a message like
	! "You can't, because ! ... is in the way." if any barrier is found.
	! The routine returns true if a barrier is found, false if not.

	_g_item = p_item;
	_g_check_take = p_checktake;

	_UpdateScope();

	_ancestor = CommonAncestor(player, p_item);
	if(_ancestor == 0) {
		! Item has been added to scope => we consider it touchable
		rfalse;
!		_ancestor = p_item;
!!		while (_ancestor && (_i = _ObjectScopedBySomething(_ancestor)) == 0)
!		while (_ancestor && (_i = 0) == 0)
!			_ancestor = parent(_ancestor);
!		if(_i ~= 0) {
!			if(ObjectIsUntouchable(_i, p_dontprint, p_checktake)) {
!				! Item immediately added to scope
!				rtrue;
!			}
!		}
	} else if(player ~= _ancestor) {
		_g_check_take = 0;
		if(_FindBarrier(_ancestor, parent(player), p_dontprint)) {
			! First, a barrier between the player and the ancestor.  The player
			! can only be in a sequence of enterable objects, and only closed
			! containers form a barrier.
			rtrue;
		}
		_g_check_take = p_checktake;
	}

	! Second, a barrier between the item and the ancestor.  The item can
	! be carried by someone, part of a piece of machinery, in or on top
	! of something and so on.
	if (p_item ~= _ancestor && _FindBarrier(_ancestor, parent(p_item), p_dontprint)) {
		rtrue;
	}
	rfalse;
];

[ TestScope p_obj _i;
	! DM: TestScope(obj,actor)
	! Tests whether the object obj is in scope.
	! The routine returns true or false.

	_UpdateScope();
#Iftrue #version_number > 3;
	@scan_table p_obj scope scope_objects 1 -> _i ?~_object_wasnt_found;
	rtrue;
._object_wasnt_found;
#Ifnot;
	for(_i = 0: _i < scope_objects: _i++) {
		if(scope->_i == p_obj) rtrue;
	}
#Endif;
	rfalse;
];

[ LoopOverScope p_routine _i _scope_count;
	! Calls routine p_routine(obj) for each object obj in scope.
	! No return value

	_scope_count = GetScopeCopy();

	for(_i = 0: _i < _scope_count: _i++) p_routine(scope_copy->_i);
];

! ####################################
!  Veneer
! ####################################

#IfDef DEBUG;
[DebugAttribute p_attr;
	print "(attribute ", p_attr, ")";
];

[ DebugParameter p_w;
	print p_w;
	if (p_w >= 1 && p_w <= top_object) print " (", (name) p_w, ")";
!	print " (value '", p_w, "')";
];

[ DebugAction p_a _anames;
	if (p_a >= 4096) { print "<fake action ", p_a-4096, ">"; return; }
	_anames = #identifiers_table;
	_anames = _anames + 2*(_anames-->0) + 2*48;
	print (string) _anames-->p_a;
];

Array direction_name_array static --> "no direction" "north" "south" "east" "west" "northeast" "northwest" "southeast" "southwest" "up" "down" "in" "out";

[ DebugDirection p_dir _n;
	_n = p_dir - N_TO_CONST + 1;
	print (string) direction_name_array-->_n;
];

[ TraceAction;
	print "[ Action ", (DebugAction) action;
	if (noun ~= 0) {
		print " with noun ", (DebugParameter) noun;
		if (second ~= 0) {
			print " and second ", (DebugParameter) second;
		}
	}
	if (direction ~= 0)
		print " with direction ", (DebugDirection) direction;
	print "]^";
];

#EndIf;

[ ActionPrimitive; return indirect(#actions_table-->action); ];

[ PerformPreparedAction _ret_val _action_returned;
#IfDef DEBUG;
	if(debug_flag & 2) TraceAction();
#EndIf;
	if ((meta || (BeforeRoutines() == false)) && action < 4096) {
		@push run_after_routines_msg; @push run_after_routines_arg_1;
		run_after_routines_msg = 0;
		_action_returned = ActionPrimitive();
		if(_action_returned ~= 0 or 1) {
			PrintMsg(_action_returned);
		}
		! If the action has set run_after_routines_msg = true, after routines
		! should be run. If it has set it to another value, this message should
		! be printed unless after routines returns true.
		if(run_after_routines_msg && AfterRoutines() == false &&
				run_after_routines_msg ~= 1 &&
				keep_silent == false)
			PrintMsg(run_after_routines_msg, run_after_routines_arg_1);
		@pull run_after_routines_arg_1; @pull run_after_routines_msg;
		_ret_val = true; ! could run the command
	}
	return _ret_val;
];

[ DirPropToFakeObj p_dir_prop;
#IfTrue RUNTIME_ERRORS > RTE_MINIMUM;
	if(p_dir_prop < N_TO_CONST || p_dir_prop > OUT_TO_CONST)
		_RunTimeError(ERR_NOT_DIR_PROP);
#EndIf;
	return p_dir_prop - N_TO_CONST + FAKE_N_OBJ;
];

[ _SetDirectionIfIsFakeDir;
	if(second >= FAKE_N_OBJ && second <= FAKE_OUT_OBJ) {
		direction = second - FAKE_N_OBJ + N_TO_CONST;
		second = 0;
	}
	if(noun >= FAKE_N_OBJ && noun <= FAKE_OUT_OBJ) {
		direction = noun - FAKE_N_OBJ + N_TO_CONST;
		noun = second;
		second = 0;
	}
];


[ PerformAction p_action p_noun p_second _sa _sn _ss _result _d; !  _sdi _sd _sinp1 _sinp2
	_sa = action; _sn = noun; _ss = second; _d = direction; ! _sinp1 = inp1; _sinp2 = inp2; _sdi = selected_direction_index; _sd = selected_direction;
	action = p_action; noun = p_noun; second = p_second; ! inp1 = p_noun; inp2 = p_second;
	! selected_direction_index = 0; selected_direction = 0;
	_SetDirectionIfIsFakeDir();
	_result = PerformPreparedAction();
	action = _sa; noun = _sn; second = _ss; direction = _d; ! selected_direction_index = _sdi; selected_direction = _sd; inp1 = _sinp1; inp2 = _sinp2;
	return _result;
];

[ R_Process p_action p_noun p_second; ! _s1 _s2;
!	_s1 = inp1; _s2 = inp2;
!	inp1 = p_noun; inp2 = p_second;
	PerformAction(p_action, p_noun, p_second);
!	inp1 = _s1; inp2 = _s2;
];



[ Unsigned__Compare p_x p_y;
	@jl p_x 0 ?_x_negative;
	! x >= 0
	@jl p_y 0 ?~_x_positive_y_positive;
	! x >= 0 and y < 0
	return -1;
._x_negative;
	@jl p_y 0 ?~rtrue; ! x < 0 and y >= 0
	! x < 0 && y < 0
._x_positive_y_positive;
	! x and y have same sign
	@jg p_x p_y ?rtrue;
	@je p_x p_y ?rfalse;
	return -1;
];

Constant UnsignedCompare = Unsigned__Compare;

#Ifndef DEBUG;
#Ifndef STRICT_MODE;
#IfTrue RUNTIME_ERRORS == RTE_MINIMUM;

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Replace some veneer routines with smaller versions
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


!   Print__PName: Print the name of a property.

[ Print__PName; ];

!   WV__Pr:  write a value to the property for the given
!			 object having the given identifier

[ WV__Pr obj identifier value x;
 x = obj..&identifier;
 if (x==0) {
	!RT__Err(\"write to\", obj, identifier);
	return;
 }
 !#ifdef INFIX;
 !if (obj has infix__watching || (debug_flag & 15)) RT__TrPS(obj,identifier,value);
 !#ifnot;
 !#ifdef DEBUG;
 !if (debug_flag & 15) RT__TrPS(obj,identifier,value);
 !#endif; #endif;
 x-->0 = value;
];

!   RV__Pr:  read a value from the property for the given
!	 		 object having the given identifier

[ RV__Pr obj identifier x;
 x = obj..&identifier;
 if (x==0) {
	!if (identifier >= 1 && identifier < 64 && obj.#identifier <= 2)
		 @get_prop obj identifier -> sp;
		 @ret_popped;
		 !return obj.identifier;
	 !RT__Err(\"read\", obj, identifier); return;
 }
 #IFV3;
 !if (obj..#identifier > 2) RT__Err(\"read\", obj, identifier);
 #IFNOT;
 !if (obj..#identifier > 2) RT__Err(\"read\", obj, identifier, 2);
 #ENDIF;
 return x-->0;
];

#Iftrue #version_number > 4;

!   CA__Pr:  call, that is, print-or-run-or-read, a property:
!			 this exactly implements obj..prop(...).  Note that
!			 classes (members of Class) have 5 built-in properties
!			 inherited from Class: create, recreate, destroy,
!			 remaining and copy.  Implementing these here prevents
!			 the need for a full metaclass inheritance scheme.

[ CA__Pr obj id a b c d e f x y z s s2 n m;
 if (obj < 1 || obj > #largest_object-255)
 {   switch(Z__Region(obj))
	 { 2: if (id == call) {
			s = sender;
			sender = self;
			self = obj;
			#ifdef action;
			sw__var=action;
			#endif;
			x = indirect(obj, a, b, c, d, e, f);
			self = sender;
			sender = s;
			return x;
		  }
		  jump Call__Error;
	   3: if (id == print) {
			@print_paddr obj;
			rtrue;
		  }
		  if (id == print_to_array) {
			@output_stream 3 a;
			@print_paddr obj;
			@output_stream -3;
			return a-->0;
		  }
		  jump Call__Error;
	 }
	 jump Call__Error;
 }
 @check_arg_count 3 ?~A__x;y++;@check_arg_count 4 ?~A__x;y++;
 @check_arg_count 5 ?~A__x;y++;@check_arg_count 6 ?~A__x;y++;
 @check_arg_count 7 ?~A__x;y++;@check_arg_count 8 ?~A__x;y++;.A__x;
 !#ifdef INFIX;if (obj has infix__watching) n=1;#endif;
 !#ifdef DEBUG;if (debug_flag & 1 ~= 0) n=1;#endif;
 !if (n==1) {
	!#ifdef DEBUG;n=debug_flag & 1; debug_flag=debug_flag-n;#endif;
	!print \"[ ~\", (name) obj, \"~.\", (property) id, \"(\";
	!switch(y)
	!{ 1: print a;
	  !2: print a,\",\",b;
	  !3: print a,\",\",b,\",\",c;
	  !4: print a,\",\",b,\",\",c,\",\",d;
	  !5: print a,\",\",b,\",\",c,\",\",d,\",\",e;
	  !6: print a,\",\",b,\",\",c,\",\",d,\",\",e,\",\",f;
	!}
	!print \") ]^\";
   !#ifdef DEBUG;debug_flag = debug_flag + n;#endif;
 !}
 if (id > 0 && id < 64) {
	!x = obj.&id;
	@get_prop_addr obj id -> x;
	if (x==0) {
		x=$000a-->0 + 2*(id-1);
		n=2;
	} else
		!n = obj.#id;
		@get_prop_len x -> n;
 } else {
	if (id>=64 && id<69 && obj in Class)
		return Cl__Ms(obj,id,y,a,b,c,d);
	x = obj..&id;
	if (x == 0) {
		.Call__Error;
		!RT__Err(\"send message\", obj, id);
		return;
	}
	n = 0->(x-1);
	if (id&$C000==$4000)
		switch (n&$C0)
			{   0: n=1;
			  $40: n=2;
			  $80: n=n&$3F;
			}
 }
 for (:2*m<n:m++)
 {  if (x-->m==$ffff) rfalse;
	switch(Z__Region(x-->m))
	{ 2: s = sender;
		 sender = self;
		 self = obj;
		 s2 = sw__var;
		 #ifdef LibSerial;
		 if (id==life) sw__var=reason_code; else sw__var=action;
		 #endif;
		 switch(y)
			{ 0: z = indirect(x-->m);
			  1: z = indirect(x-->m, a);
			  2: z = indirect(x-->m, a, b);
			  3: z = indirect(x-->m, a, b, c);
			  4: z = indirect(x-->m, a, b, c, d);
			  5: z = indirect(x-->m, a, b, c, d, e);
			  6: z = indirect(x-->m, a, b, c, d, e, f);
			}
		 self = sender;
		 sender = s;
		 sw__var = s2;
		 if (z ~= 0) return z;
	  3: print_ret (string) x-->m;
	  default: return x-->m;
	}
 }
 rfalse;
];

[ Cl__Ms obj id y a b c d x;
 switch(id)
 {   create:
		 if (children(obj)<=1) rfalse;
		 x=child(obj);
		 remove x;
		 if (x provides create) {
			if (y==0) x.create();
			if (y==1) x.create(a);
			if (y==2) x.create(a,b);
			!if (y>3) RT__Err(1,obj);
			if (y>=3) x.create(a,b,c);
		 }
		 return x;
	 recreate:
		 if (~~(a ofclass obj)) {
			!RT__Err(\"recreate\", a, -obj);
			rfalse;
 		 }
		 Copy__Primitive(a, child(obj));
		 if (a provides create) {
			if (y==1) a.create();
			if (y==2) a.create(b);
			if (y==3) a.create(b,c);
			!if (y>4) RT__Err(1,obj);
			if (y>=4) a.create(b,c,d);
		 }
		 rfalse;
	 destroy:
		 if (~~(a ofclass obj)) {
			!RT__Err(\"destroy\", a, -obj);
			rfalse;
		 }
		 if (a provides destroy) a.destroy();
		 Copy__Primitive(a, child(obj));
		 move a to obj;
		 rfalse;
	 remaining:
		 return children(obj)-1;
	 copy:
		 if (~~(a ofclass obj)) {
			!RT__Err(\"copy\", a, -obj);
			rfalse;
		 }
		 if (~~(b ofclass obj)) {
			!RT__Err(\"copy\", b, -obj);
			rfalse;
		 }
		 Copy__Primitive(a, b);
		 rfalse;
 }
];

#Endif; ! #Iftrue #version_number > 4;

!   IB__Pr:  ++(individual property)

[ IB__Pr obj identifier x;
 x = obj..&identifier;
 if (x==0) {
	!RT__Err(\"increment\", obj, identifier);
	return;
 }
 !#ifdef INFIX;
 !if (obj has infix__watching || (debug_flag & 15)) RT__TrPS(obj,identifier,(x-->0)+1);
 !#ifnot; #ifdef DEBUG;
 !if (debug_flag & 15) RT__TrPS(obj,identifier,(x-->0)+1);
 !#endif; #endif;
 return ++(x-->0);
];

!   IA__Pr:  (individual property)++

[ IA__Pr obj identifier x;
 x = obj..&identifier;
 if (x==0) {
	!RT__Err(\"increment\", obj, identifier);
	return;
 }
 !#ifdef INFIX;
 !if (obj has infix__watching || (debug_flag & 15))
 !RT__TrPS(obj,identifier,(x-->0)+1);
 !#ifnot; #ifdef DEBUG;
 !if (debug_flag & 15) RT__TrPS(obj,identifier,(x-->0)+1);
 !#endif; #endif;
 return (x-->0)++;
];

!   DB__Pr:  --(individual property)

[ DB__Pr obj identifier x;
 x = obj..&identifier;
 if (x==0) {
	!RT__Err(\"decrement\", obj, identifier);
	return;
 }
 !#ifdef INFIX;
 !if (obj has infix__watching || (debug_flag & 15)) RT__TrPS(obj,identifier,(x-->0)-1);
 !#ifnot; #ifdef DEBUG;
 !if (debug_flag & 15) RT__TrPS(obj,identifier,(x-->0)-1);
 !#endif; #endif;
 return --(x-->0);
];

!   DA__Pr:  (individual property)--

[ DA__Pr obj identifier x;
 x = obj..&identifier;
 if (x==0) {
	!RT__Err(\"decrement\", obj, identifier);
	return;
 }
 !#ifdef INFIX;
 !if (obj has infix__watching || (debug_flag & 15)) RT__TrPS(obj,identifier,(x-->0)-1);
 !#ifnot; #ifdef DEBUG;
 !if (debug_flag & 15) RT__TrPS(obj,identifier,(x-->0)-1);
 !#endif; #endif;
 return (x-->0)--;
];

!   RA__Pr:  read the address of a property value for a given object,
!			 returning 0 if it doesn't provide this individual
!			 property

[ RA__Pr obj identifier i otherid cla;
 if (obj==0) rfalse;
 if (identifier<64 && identifier>0) {
	 !return obj.&identifier;
	 @get_prop_addr obj identifier -> sp;
	 @ret_popped;
 }
 if (identifier & $8000 ~= 0)
 {   cla = #classes_table-->(identifier & $ff);
	 if (cla.&3 == 0) rfalse;
	 if (~~(obj ofclass cla)) rfalse;
	 identifier = (identifier & $7f00) / $100;
	 i = cla.3;
	 while (identifier>0)
	 {   identifier--;
		 i = i + i->2 + 3;
	 }
	 return i+3;
 }
 if (identifier & $4000 ~= 0)
 {   cla = #classes_table-->(identifier & $ff);
	 identifier = (identifier & $3f00) / $100;
	 if (~~(obj ofclass cla)) rfalse; i=0-->5;
	 if (cla == 2) return i+2*identifier-2;
	 i = 0-->((i+124+cla*14)/2);
	 i = CP__Tab(i + 2*(0->i) + 1, -1)+6;
	 return CP__Tab(i, identifier);
 }
 if (obj.&3 == 0) rfalse;
 if (obj in 1)
 {  	 if (identifier<64 || identifier>=72) rfalse;
 }
 if (self == obj)
	 otherid = identifier | $8000;
 i = obj.3;
 while (i-->0 ~= 0)
 {	if (i-->0 == identifier or otherid)
		return i+3;
	 i = i + i->2 + 3;
 }
 rfalse;
];

!   RL__Pr:  read the property length of an individual property value,
!		 	 returning 0 if it isn't provided by the given object

[ RL__Pr obj identifier x;
 if (identifier<64 && identifier>0) {
	!return obj.#identifier;
	@get_prop_addr obj identifier -> x;
	@get_prop_len x -> sp;
	@ret_popped;
 }
 x = obj..&identifier;
 if (x==0) rfalse;
 if (identifier&$C000==$4000)
	 switch (((x-1)->0)&$C0)
	 {	0: return 1;
		$40: return 2;
		$80: return ((x-1)->0)&$3F;
	 }
 return (x-1)->0;
];

!   RA__Sc:  implement the "superclass" (::) operator,
!			 returning an identifier

[ RA__Sc cla identifier otherid i j k;
 if (cla notin 1 && cla > 4)
 {
	!RT__Err(\"be a ' :: ' superclass\", cla, -1);
	rfalse;
 }
 if (self ofclass cla) otherid = identifier | $8000;
 for (j=0: #classes_table-->j ~= 0: j++)
 {   if (cla==#classes_table-->j)
	 {   if (identifier < 64) return $4000 + identifier*$100 + j;
		 if (cla.&3 == 0) break;
		 i = cla.3;
		 while (i-->0 ~= 0)
		 {   if (i-->0 == identifier or otherid)
				 return $8000 + k*$100 + j;
			 i = i + i->2 + 3;
			 k++;
		 }
		 break;
	 }
 }
 !RT__Err(\"make use of\", cla, identifier);
 rfalse;
 ];

!   OP__Pr:  test whether or not given object provides individual
!			 property with the given identifier code

[ OP__Pr obj identifier x;
 if (obj<1 || obj > (#largest_object-255))
 {   if (identifier ~= print or print_to_array or call) rfalse;
	 switch(Z__Region(obj))
	 {   2: if (identifier == call) rtrue;
		 3: if (identifier == print or print_to_array) rtrue;
	 }
	 rfalse;
 }
 if (identifier<64)
 {   @get_prop_addr obj identifier -> x;
	 if (x ~= 0) rtrue;
	 !if (obj.&identifier ~= 0) rtrue;
	 rfalse;
 }
 if (obj..&identifier ~= 0) rtrue;
 if (identifier<72 && obj in 1) rtrue;
 rfalse;
];

!   OC__Cl:  test whether or not given object is of the given class

[ OC__Cl obj cla j a n;
 if (obj<1 || obj > (#largest_object-255))
 {   if (cla ~= 3 or 4) rfalse;
	 if (Z__Region(obj) == cla-1) rtrue;
	 rfalse;
 }
 if (cla == 1) {
	 if (obj<=4) rtrue;
	 if (obj in 1) rtrue;
	 rfalse;
 } else if (cla == 2) {
	 if (obj<=4) rfalse;
	 if (obj in 1) rfalse;
	 rtrue;
 } else if (cla == 3 or 4) {
	 rfalse;
 }
 if (cla notin 1) {
	!RT__Err(\"apply ' ofclass ' for\", cla, -1);
	rfalse;
 }
 @get_prop_addr obj 2 -> a;
 if (a==0) rfalse;
 @get_prop_len a -> n;
 for (j=0: j<n/2: j++) {
	if (a-->j == cla) rtrue;
 }
 rfalse;
];


#Endif;
#Endif;
#Endif;


#Iftrue #version_number < 5;
! These routines are implemented by Veneer, but the default implementations give compile errors for z3

! [ Print__PName prop p size cla i;
	 ! if (prop & $c000)
	 ! {   cla = #classes_table-->(prop & $ff);
		 ! print (name) cla, "::";
		 ! if ((prop & $8000) == 0) prop = (prop & $3f00)/$100;
		 ! else
		 ! {   prop = (prop & $7f00)/$100;
			 ! i = cla.3;
			 ! while ((i-->0 ~= 0) && (prop>0))
			 ! {   i = i + i->2 + 3;
				 ! prop--;
			 ! }
			 ! prop = (i-->0) & $7fff;
		 ! }
	 ! }
	 ! p = #identifiers_table;
	 ! size = p-->0;
	 ! if (prop<=0 || prop>=size || p-->prop==0)
		 ! print "<number ", prop, ">";
	 ! else print (string) p-->prop;
 ! ];

! [ FindIndivPropValue p_obj p_property _x _prop_id;
	! _x = p_obj.3;
	! if (_x == 0) rfalse;
	! !  print "Table for ", (object) obj, " is at ", (hex) x, "^";
	! while (true) {
		! _prop_id = _x-->0;
		! if(_prop_id == 0) break;
		! if(_prop_id & 32767 == p_property) break;
		! ! print (hex) x-->0, " (", (property) x-->0, ")  length ", x->2, ": ";
		! !	   for (n = 0: n< (x->2)/2: n++)
		! !		   print (hex) (x+3)-->n, " ";
		! !	   @new_line;
		! _x = _x + _x->2 + 3;
	! }
	! return _x;
! ];

! [ RV__Pr p_object p_property _value _address;
	! if(p_object == 0) {
		! print "*Error: Tried to read property ";
		! Print__PName(p_property);
		! " of nothing.*";
	! }
	! if(p_object provides p_property) {
		! if(p_property >= INDIV_PROP_START) {
			! _address = FindIndivPropValue(p_object, p_property);
			! return (_address + 3)-->0;
		! }
		! @get_prop p_object p_property -> _value;
		! return _value;
	! }
	! print "[Error: Tried to read undefined property ";
	! Print__PName(p_property);
	! print " of ";
	! PrintShortName(p_object);
	! print "]";
	! rfalse;
! ];

!	  CA__Pr:  call, that is, print-or-run-or-read, a property:
!					  this exactly implements obj..prop(...).  Note that
!					  classes (members of Class) have 5 built-in properties
!					  inherited from Class: create, recreate, destroy,
!					  remaining and copy.  Implementing these here prevents
!					  the need for a full metaclass inheritance scheme.	  */

[ CA__Pr obj id a	x z s s2 n m;
! print "CA_Pr obj = ", obj,", id = ", id,", a = ", a, "^";
	if (obj < 1 || obj > #largest_object-255) {
		switch(Z__Region(obj)) {
			2:
			if (id == call) {
				s = sender; sender = self; self = obj;
				#ifdef action;sw__var=action;#endif;
				x = indirect(obj, a);
				self = sender; sender = s; return x;
			}
			jump Call__Error;
			3:
			if (id == print) { @print_paddr obj; rtrue; }
			if (id == print_to_array) {
				@output_stream 3 a; @print_paddr obj; @output_stream -3;
				return a-->0;
			}
			jump Call__Error;
		}
		jump Call__Error;
	}
! print "CA_Pr(2) obj = ", obj,", id = ", id,", a = ", a, "^";
!   @check_arg_count 3 ?~A__x;y++;@check_arg_count 4 ?~A__x;y++;
!   @check_arg_count 5 ?~A__x;y++;@check_arg_count 6 ?~A__x;y++;
!   @check_arg_count 7 ?~A__x;y++;@check_arg_count 8 ?~A__x;y++;.A__x;
!   #ifdef INFIX;if (obj has infix__watching) n=1;#endif;
	#ifdef DEBUG;if (debug_flag & 1 ~= 0) n=1;#endif;
!   if (n==1) {
!	 n=debug_flag & 1; debug_flag=debug_flag-n;
!	 print "[ ~", (name) obj, "~.", (property) id, "(";
!	 switch(y) {
!	 1:
!	   print a; 2: print a,",",b; 3: print a,",",b,",",c;
!	 4:
!	   print a,",",b,",",c,",",d;
!	 5:
!	   print a,",",b,",",c,",",d,",",e;
!	 6:
!	   print a,",",b,",",c,",",d,",",e,",",f;
!	 }
!	 print ") ]^"; debug_flag = debug_flag + n;
!   }
	if (id > 0 && id < INDIV_PROP_START) {
!   print "CA_Pr OK obj = ", obj,", id = ", id,", a = ", a, "^";
		x = obj.&id;
		if (x==0) {
			x=$000a-->0 + 2*(id-1); n=2;
		} else n = obj.#id;
	} else {
		if (id>=64 && id<69 && obj in Class) {
!	 print "CA_Pr ERROR0 obj = ", obj,", id = ", id,", a = ", a, "^";
#IfTrue RUNTIME_ERRORS > RTE_MINIMUM;
			RT__Err("Class create etc", obj, id);
#Endif;
			return;
!	 return Cl__Ms(obj,id,y,a,b,c);
		}
!   print "CA_Pr(2.1) obj = ", obj,", id = ", id,", n = ", n, "^";
		x = obj..&id;
!   print "CA_Pr(2.2) obj = ", obj,", id = ", id,", x = ", x, "^";
		if (x == 0) {
!	 print "CA_Pr ERROR1 obj = ", obj,", id = ", id,", a = ", a, "^";
			.Call__Error;
#IfTrue RUNTIME_ERRORS > RTE_MINIMUM;
			RT__Err("send message", obj, id);
#Endif;
			return;
		}
!   print "Reading n at ", x-1,": ", 0->(x-1), "^";
		n = 0->(x-1);
		if (id&$C000==$4000)
		switch (n&$C0) { 0: n=1; $40: n=2; $80: n=n&$3F; }
	}
! print "CA_Pr(3) obj = ", obj,", id = ", id,", a = ", a, "^";
	for (:m+m<n:m++) {
		z = x-->m;
!   print "Considering routine at ", x+2*m,": ", z, "^";
		if (z==$ffff) rfalse;
		switch(Z__Region(z)) {
		2:
			s = sender; sender = self; self = obj; s2 = sw__var;
!	   switch(y) {
!	   0:
!		 z = indirect(x-->m);
!	   1:
			if(a)
				z = indirect(z, a);
			else
				z = indirect(z);
!	   2:
!		 z = indirect(x-->m, a, b);
!	   3:
!	   z = indirect(x-->m, a, b, c);
!	   4:
!		 z = indirect(x-->m, a, b, c, d);
!	   5:
!		 z = indirect(x-->m, a, b, c, d, e);
!	   6:
!		 z = indirect(x-->m, a, b, c, d, e, f);
!	   }
			self = sender; sender = s; sw__var = s2;
			if (z ~= 0) return z;
		3:
			print_ret (string) z;
		default:
			return z;
		}
	}
	rfalse;
];

[ Cl__Ms;
	rfalse;
];
#EndIf;

#IfTrue RUNTIME_ERRORS < RTE_VERBOSE;
[RT__Err err_no par1 par2;
	print "Inform error: ";
	if(err_no ofclass String)
		print (string) err_no, " - ";
	else
		print_ret err_no;
	print_ret " (", par1, ", ", par2, ")";
];
#EndIf;
