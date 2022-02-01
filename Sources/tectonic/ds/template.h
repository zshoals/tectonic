#pragma once

#define stringify_expand(elem) #elem
#define _tec_stringify(elem) stringify_expand(elem)

#define _tec_concat(a, b) a ## b
#define _tec_paste(a, b) _tec_concat(a, b)

#define _tec_bfa_makename(prefix, type, count) _tec_paste(_tec_paste(prefix, type), _tec_paste(_, count))

//This is the same for now, but at one point appended _t, leaving here for legacy purposes
#define _tec_bfa_makename_t(prefix, type, count) _tec_bfa_makename(prefix, type, count)

#define _tec_func(func_suffix) _tec_paste(_tec_me, func_suffix)