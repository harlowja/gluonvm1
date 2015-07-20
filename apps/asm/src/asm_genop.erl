%%% Generated by codegen/genop.py
-module(asm_genop).
-export([arity/1, name/1, opcode/1]).

arity('label') -> 1;
arity('func_info') -> 3;
arity('int_code_end') -> 0;
arity('call') -> 2;
arity('call_last') -> 3;
arity('call_only') -> 2;
arity('call_ext') -> 2;
arity('call_ext_last') -> 3;
arity('bif0') -> 2;
arity('bif1') -> 4;
arity('bif2') -> 5;
arity('allocate') -> 2;
arity('allocate_heap') -> 3;
arity('allocate_zero') -> 2;
arity('allocate_heap_zero') -> 3;
arity('test_heap') -> 2;
arity('init') -> 1;
arity('deallocate') -> 1;
arity('return') -> 0;
arity('send') -> 0;
arity('remove_message') -> 0;
arity('timeout') -> 0;
arity('loop_rec') -> 2;
arity('loop_rec_end') -> 1;
arity('wait') -> 1;
arity('wait_timeout') -> 2;
arity('m_plus') -> 4;
arity('m_minus') -> 4;
arity('m_times') -> 4;
arity('m_div') -> 4;
arity('int_div') -> 4;
arity('int_rem') -> 4;
arity('int_band') -> 4;
arity('int_bor') -> 4;
arity('int_bxor') -> 4;
arity('int_bsl') -> 4;
arity('int_bsr') -> 4;
arity('int_bnot') -> 3;
arity('is_lt') -> 3;
arity('is_ge') -> 3;
arity('is_eq') -> 3;
arity('is_ne') -> 3;
arity('is_eq_exact') -> 3;
arity('is_ne_exact') -> 3;
arity('is_integer') -> 2;
arity('is_float') -> 2;
arity('is_number') -> 2;
arity('is_atom') -> 2;
arity('is_pid') -> 2;
arity('is_reference') -> 2;
arity('is_port') -> 2;
arity('is_nil') -> 2;
arity('is_binary') -> 2;
arity('is_constant') -> 2;
arity('is_list') -> 2;
arity('is_nonempty_list') -> 2;
arity('is_tuple') -> 2;
arity('test_arity') -> 3;
arity('select_val') -> 3;
arity('select_tuple_arity') -> 3;
arity('jump') -> 1;
arity('catch') -> 2;
arity('catch_end') -> 1;
arity('move') -> 2;
arity('get_list') -> 3;
arity('get_tuple_element') -> 3;
arity('set_tuple_element') -> 3;
arity('put_string') -> 3;
arity('put_list') -> 3;
arity('put_tuple') -> 2;
arity('put') -> 1;
arity('badmatch') -> 1;
arity('if_end') -> 0;
arity('case_end') -> 1;
arity('call_fun') -> 1;
arity('make_fun') -> 3;
arity('is_function') -> 2;
arity('call_ext_only') -> 2;
arity('bs_start_match') -> 2;
arity('bs_get_integer') -> 5;
arity('bs_get_float') -> 5;
arity('bs_get_binary') -> 5;
arity('bs_skip_bits') -> 4;
arity('bs_test_tail') -> 2;
arity('bs_save') -> 1;
arity('bs_restore') -> 1;
arity('bs_init') -> 2;
arity('bs_final') -> 2;
arity('bs_put_integer') -> 5;
arity('bs_put_binary') -> 5;
arity('bs_put_float') -> 5;
arity('bs_put_string') -> 2;
arity('bs_need_buf') -> 1;
arity('fclearerror') -> 0;
arity('fcheckerror') -> 1;
arity('fmove') -> 2;
arity('fconv') -> 2;
arity('fadd') -> 4;
arity('fsub') -> 4;
arity('fmul') -> 4;
arity('fdiv') -> 4;
arity('fnegate') -> 3;
arity('make_fun2') -> 1;
arity('try') -> 2;
arity('try_end') -> 1;
arity('try_case') -> 1;
arity('try_case_end') -> 1;
arity('raise') -> 2;
arity('bs_init2') -> 6;
arity('bs_bits_to_bytes') -> 3;
arity('bs_add') -> 5;
arity('apply') -> 1;
arity('apply_last') -> 2;
arity('is_boolean') -> 2;
arity('is_function2') -> 3;
arity('bs_start_match2') -> 5;
arity('bs_get_integer2') -> 7;
arity('bs_get_float2') -> 7;
arity('bs_get_binary2') -> 7;
arity('bs_skip_bits2') -> 5;
arity('bs_test_tail2') -> 3;
arity('bs_save2') -> 2;
arity('bs_restore2') -> 2;
arity('gc_bif1') -> 5;
arity('gc_bif2') -> 6;
arity('bs_final2') -> 2;
arity('bs_bits_to_bytes2') -> 2;
arity('put_literal') -> 2;
arity('is_bitstr') -> 2;
arity('bs_context_to_binary') -> 1;
arity('bs_test_unit') -> 3;
arity('bs_match_string') -> 4;
arity('bs_init_writable') -> 0;
arity('bs_append') -> 8;
arity('bs_private_append') -> 6;
arity('trim') -> 2;
arity('bs_init_bits') -> 6;
arity('bs_get_utf8') -> 5;
arity('bs_skip_utf8') -> 4;
arity('bs_get_utf16') -> 5;
arity('bs_skip_utf16') -> 4;
arity('bs_get_utf32') -> 5;
arity('bs_skip_utf32') -> 4;
arity('bs_utf8_size') -> 3;
arity('bs_put_utf8') -> 3;
arity('bs_utf16_size') -> 3;
arity('bs_put_utf16') -> 3;
arity('bs_put_utf32') -> 3;
arity('on_load') -> 0;
arity('recv_mark') -> 1;
arity('recv_set') -> 1;
arity('gc_bif3') -> 7;
arity('line') -> 1;
arity('put_map_assoc') -> 5;
arity('put_map_exact') -> 5;
arity('is_map') -> 2;
arity('has_map_fields') -> 3;
arity('get_map_elements') -> 3;
arity(X) -> erlang:error({bad_arity, X}).

name(1) -> 'label';
name(2) -> 'func_info';
name(3) -> 'int_code_end';
name(4) -> 'call';
name(5) -> 'call_last';
name(6) -> 'call_only';
name(7) -> 'call_ext';
name(8) -> 'call_ext_last';
name(9) -> 'bif0';
name(10) -> 'bif1';
name(11) -> 'bif2';
name(12) -> 'allocate';
name(13) -> 'allocate_heap';
name(14) -> 'allocate_zero';
name(15) -> 'allocate_heap_zero';
name(16) -> 'test_heap';
name(17) -> 'init';
name(18) -> 'deallocate';
name(19) -> 'return';
name(20) -> 'send';
name(21) -> 'remove_message';
name(22) -> 'timeout';
name(23) -> 'loop_rec';
name(24) -> 'loop_rec_end';
name(25) -> 'wait';
name(26) -> 'wait_timeout';
name(27) -> 'm_plus';
name(28) -> 'm_minus';
name(29) -> 'm_times';
name(30) -> 'm_div';
name(31) -> 'int_div';
name(32) -> 'int_rem';
name(33) -> 'int_band';
name(34) -> 'int_bor';
name(35) -> 'int_bxor';
name(36) -> 'int_bsl';
name(37) -> 'int_bsr';
name(38) -> 'int_bnot';
name(39) -> 'is_lt';
name(40) -> 'is_ge';
name(41) -> 'is_eq';
name(42) -> 'is_ne';
name(43) -> 'is_eq_exact';
name(44) -> 'is_ne_exact';
name(45) -> 'is_integer';
name(46) -> 'is_float';
name(47) -> 'is_number';
name(48) -> 'is_atom';
name(49) -> 'is_pid';
name(50) -> 'is_reference';
name(51) -> 'is_port';
name(52) -> 'is_nil';
name(53) -> 'is_binary';
name(54) -> 'is_constant';
name(55) -> 'is_list';
name(56) -> 'is_nonempty_list';
name(57) -> 'is_tuple';
name(58) -> 'test_arity';
name(59) -> 'select_val';
name(60) -> 'select_tuple_arity';
name(61) -> 'jump';
name(62) -> 'catch';
name(63) -> 'catch_end';
name(64) -> 'move';
name(65) -> 'get_list';
name(66) -> 'get_tuple_element';
name(67) -> 'set_tuple_element';
name(68) -> 'put_string';
name(69) -> 'put_list';
name(70) -> 'put_tuple';
name(71) -> 'put';
name(72) -> 'badmatch';
name(73) -> 'if_end';
name(74) -> 'case_end';
name(75) -> 'call_fun';
name(76) -> 'make_fun';
name(77) -> 'is_function';
name(78) -> 'call_ext_only';
name(79) -> 'bs_start_match';
name(80) -> 'bs_get_integer';
name(81) -> 'bs_get_float';
name(82) -> 'bs_get_binary';
name(83) -> 'bs_skip_bits';
name(84) -> 'bs_test_tail';
name(85) -> 'bs_save';
name(86) -> 'bs_restore';
name(87) -> 'bs_init';
name(88) -> 'bs_final';
name(89) -> 'bs_put_integer';
name(90) -> 'bs_put_binary';
name(91) -> 'bs_put_float';
name(92) -> 'bs_put_string';
name(93) -> 'bs_need_buf';
name(94) -> 'fclearerror';
name(95) -> 'fcheckerror';
name(96) -> 'fmove';
name(97) -> 'fconv';
name(98) -> 'fadd';
name(99) -> 'fsub';
name(100) -> 'fmul';
name(101) -> 'fdiv';
name(102) -> 'fnegate';
name(103) -> 'make_fun2';
name(104) -> 'try';
name(105) -> 'try_end';
name(106) -> 'try_case';
name(107) -> 'try_case_end';
name(108) -> 'raise';
name(109) -> 'bs_init2';
name(110) -> 'bs_bits_to_bytes';
name(111) -> 'bs_add';
name(112) -> 'apply';
name(113) -> 'apply_last';
name(114) -> 'is_boolean';
name(115) -> 'is_function2';
name(116) -> 'bs_start_match2';
name(117) -> 'bs_get_integer2';
name(118) -> 'bs_get_float2';
name(119) -> 'bs_get_binary2';
name(120) -> 'bs_skip_bits2';
name(121) -> 'bs_test_tail2';
name(122) -> 'bs_save2';
name(123) -> 'bs_restore2';
name(124) -> 'gc_bif1';
name(125) -> 'gc_bif2';
name(126) -> 'bs_final2';
name(127) -> 'bs_bits_to_bytes2';
name(128) -> 'put_literal';
name(129) -> 'is_bitstr';
name(130) -> 'bs_context_to_binary';
name(131) -> 'bs_test_unit';
name(132) -> 'bs_match_string';
name(133) -> 'bs_init_writable';
name(134) -> 'bs_append';
name(135) -> 'bs_private_append';
name(136) -> 'trim';
name(137) -> 'bs_init_bits';
name(138) -> 'bs_get_utf8';
name(139) -> 'bs_skip_utf8';
name(140) -> 'bs_get_utf16';
name(141) -> 'bs_skip_utf16';
name(142) -> 'bs_get_utf32';
name(143) -> 'bs_skip_utf32';
name(144) -> 'bs_utf8_size';
name(145) -> 'bs_put_utf8';
name(146) -> 'bs_utf16_size';
name(147) -> 'bs_put_utf16';
name(148) -> 'bs_put_utf32';
name(149) -> 'on_load';
name(150) -> 'recv_mark';
name(151) -> 'recv_set';
name(152) -> 'gc_bif3';
name(153) -> 'line';
name(154) -> 'put_map_assoc';
name(155) -> 'put_map_exact';
name(156) -> 'is_map';
name(157) -> 'has_map_fields';
name(158) -> 'get_map_elements';
name(X) -> erlang:error({bad_name, X}).

opcode('label') -> 1;
opcode('func_info') -> 2;
opcode('int_code_end') -> 3;
opcode('call') -> 4;
opcode('call_last') -> 5;
opcode('call_only') -> 6;
opcode('call_ext') -> 7;
opcode('call_ext_last') -> 8;
opcode('bif0') -> 9;
opcode('bif1') -> 10;
opcode('bif2') -> 11;
opcode('allocate') -> 12;
opcode('allocate_heap') -> 13;
opcode('allocate_zero') -> 14;
opcode('allocate_heap_zero') -> 15;
opcode('test_heap') -> 16;
opcode('init') -> 17;
opcode('deallocate') -> 18;
opcode('return') -> 19;
opcode('send') -> 20;
opcode('remove_message') -> 21;
opcode('timeout') -> 22;
opcode('loop_rec') -> 23;
opcode('loop_rec_end') -> 24;
opcode('wait') -> 25;
opcode('wait_timeout') -> 26;
opcode('m_plus') -> 27;
opcode('m_minus') -> 28;
opcode('m_times') -> 29;
opcode('m_div') -> 30;
opcode('int_div') -> 31;
opcode('int_rem') -> 32;
opcode('int_band') -> 33;
opcode('int_bor') -> 34;
opcode('int_bxor') -> 35;
opcode('int_bsl') -> 36;
opcode('int_bsr') -> 37;
opcode('int_bnot') -> 38;
opcode('is_lt') -> 39;
opcode('is_ge') -> 40;
opcode('is_eq') -> 41;
opcode('is_ne') -> 42;
opcode('is_eq_exact') -> 43;
opcode('is_ne_exact') -> 44;
opcode('is_integer') -> 45;
opcode('is_float') -> 46;
opcode('is_number') -> 47;
opcode('is_atom') -> 48;
opcode('is_pid') -> 49;
opcode('is_reference') -> 50;
opcode('is_port') -> 51;
opcode('is_nil') -> 52;
opcode('is_binary') -> 53;
opcode('is_constant') -> 54;
opcode('is_list') -> 55;
opcode('is_nonempty_list') -> 56;
opcode('is_tuple') -> 57;
opcode('test_arity') -> 58;
opcode('select_val') -> 59;
opcode('select_tuple_arity') -> 60;
opcode('jump') -> 61;
opcode('catch') -> 62;
opcode('catch_end') -> 63;
opcode('move') -> 64;
opcode('get_list') -> 65;
opcode('get_tuple_element') -> 66;
opcode('set_tuple_element') -> 67;
opcode('put_string') -> 68;
opcode('put_list') -> 69;
opcode('put_tuple') -> 70;
opcode('put') -> 71;
opcode('badmatch') -> 72;
opcode('if_end') -> 73;
opcode('case_end') -> 74;
opcode('call_fun') -> 75;
opcode('make_fun') -> 76;
opcode('is_function') -> 77;
opcode('call_ext_only') -> 78;
opcode('bs_start_match') -> 79;
opcode('bs_get_integer') -> 80;
opcode('bs_get_float') -> 81;
opcode('bs_get_binary') -> 82;
opcode('bs_skip_bits') -> 83;
opcode('bs_test_tail') -> 84;
opcode('bs_save') -> 85;
opcode('bs_restore') -> 86;
opcode('bs_init') -> 87;
opcode('bs_final') -> 88;
opcode('bs_put_integer') -> 89;
opcode('bs_put_binary') -> 90;
opcode('bs_put_float') -> 91;
opcode('bs_put_string') -> 92;
opcode('bs_need_buf') -> 93;
opcode('fclearerror') -> 94;
opcode('fcheckerror') -> 95;
opcode('fmove') -> 96;
opcode('fconv') -> 97;
opcode('fadd') -> 98;
opcode('fsub') -> 99;
opcode('fmul') -> 100;
opcode('fdiv') -> 101;
opcode('fnegate') -> 102;
opcode('make_fun2') -> 103;
opcode('try') -> 104;
opcode('try_end') -> 105;
opcode('try_case') -> 106;
opcode('try_case_end') -> 107;
opcode('raise') -> 108;
opcode('bs_init2') -> 109;
opcode('bs_bits_to_bytes') -> 110;
opcode('bs_add') -> 111;
opcode('apply') -> 112;
opcode('apply_last') -> 113;
opcode('is_boolean') -> 114;
opcode('is_function2') -> 115;
opcode('bs_start_match2') -> 116;
opcode('bs_get_integer2') -> 117;
opcode('bs_get_float2') -> 118;
opcode('bs_get_binary2') -> 119;
opcode('bs_skip_bits2') -> 120;
opcode('bs_test_tail2') -> 121;
opcode('bs_save2') -> 122;
opcode('bs_restore2') -> 123;
opcode('gc_bif1') -> 124;
opcode('gc_bif2') -> 125;
opcode('bs_final2') -> 126;
opcode('bs_bits_to_bytes2') -> 127;
opcode('put_literal') -> 128;
opcode('is_bitstr') -> 129;
opcode('bs_context_to_binary') -> 130;
opcode('bs_test_unit') -> 131;
opcode('bs_match_string') -> 132;
opcode('bs_init_writable') -> 133;
opcode('bs_append') -> 134;
opcode('bs_private_append') -> 135;
opcode('trim') -> 136;
opcode('bs_init_bits') -> 137;
opcode('bs_get_utf8') -> 138;
opcode('bs_skip_utf8') -> 139;
opcode('bs_get_utf16') -> 140;
opcode('bs_skip_utf16') -> 141;
opcode('bs_get_utf32') -> 142;
opcode('bs_skip_utf32') -> 143;
opcode('bs_utf8_size') -> 144;
opcode('bs_put_utf8') -> 145;
opcode('bs_utf16_size') -> 146;
opcode('bs_put_utf16') -> 147;
opcode('bs_put_utf32') -> 148;
opcode('on_load') -> 149;
opcode('recv_mark') -> 150;
opcode('recv_set') -> 151;
opcode('gc_bif3') -> 152;
opcode('line') -> 153;
opcode('put_map_assoc') -> 154;
opcode('put_map_exact') -> 155;
opcode('is_map') -> 156;
opcode('has_map_fields') -> 157;
opcode('get_map_elements') -> 158;
opcode(X) -> erlang:error({bad_opcode, X}).

