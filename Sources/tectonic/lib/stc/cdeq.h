/* MIT License
 *
 * Copyright (c) 2021 Tyge Løvset, NORCE, www.norceresearch.no
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CDEQ_H_INCLUDED
#include "ccommon.h"
#include "forward.h"
#include <stdlib.h>
#include <string.h>

struct cdeq_rep { size_t size, cap; void* base[]; };
#define cdeq_rep_(self) c_container_of((self)->_base, struct cdeq_rep, base)
#endif // CDEQ_H_INCLUDED

#ifndef i_prefix
#define i_prefix cdeq_
#endif
#include "template.h"

#if !defined i_fwd
_cx_deftypes(_c_cdeq_types, _cx_self, i_val);
#endif
typedef i_valraw _cx_rawvalue;

STC_API _cx_self        _cx_memb(_init)(void);
STC_API _cx_self        _cx_memb(_clone)(_cx_self cx);
STC_API void            _cx_memb(_clear)(_cx_self* self);
STC_API void            _cx_memb(_del)(_cx_self* self);
STC_API _cx_value*      _cx_memb(_push_back)(_cx_self* self, i_val value);
STC_API void            _cx_memb(_expand_right_half_)(_cx_self* self, size_t idx, size_t n);

#ifndef i_queue
STC_API _cx_iter        _cx_memb(_find_in)(_cx_iter p1, _cx_iter p2, i_valraw raw);
STC_API int             _cx_memb(_value_compare)(const _cx_value* x, const _cx_value* y);
STC_API _cx_value*      _cx_memb(_push_front)(_cx_self* self, i_val value);
STC_API _cx_iter        _cx_memb(_erase_range_p)(_cx_self* self, _cx_value* p1, _cx_value* p2);
STC_API _cx_iter        _cx_memb(_insert_range_p)(_cx_self* self, _cx_value* pos,
                                                  const _cx_value* p1, const _cx_value* p2, bool clone);
STC_API _cx_iter        _cx_memb(_emplace_range_p)(_cx_self* self, _cx_value* pos,
                                                   const _cx_rawvalue* p1, const _cx_rawvalue* p2);
#endif // i_queue

STC_INLINE bool         _cx_memb(_empty)(_cx_self cx) { return !cdeq_rep_(&cx)->size; }
STC_INLINE size_t       _cx_memb(_size)(_cx_self cx) { return cdeq_rep_(&cx)->size; }
STC_INLINE size_t       _cx_memb(_capacity)(_cx_self cx) { return cdeq_rep_(&cx)->cap; }
STC_INLINE void         _cx_memb(_swap)(_cx_self* a, _cx_self* b) {c_swap(_cx_self, *a, *b); }
STC_INLINE i_val        _cx_memb(_value_fromraw)(i_valraw raw) { return i_valfrom(raw); }
STC_INLINE i_valraw     _cx_memb(_value_toraw)(_cx_value* pval) { return i_valto(pval); }
STC_INLINE i_val        _cx_memb(_value_clone)(i_val val)
                            { return i_valfrom(i_valto(&val)); }
STC_INLINE void         _cx_memb(_copy)(_cx_self *self, _cx_self other) {
                            if (self->data == other.data) return;
                            _cx_memb(_del)(self); *self = _cx_memb(_clone)(other);
                        }
STC_INLINE _cx_value*   _cx_memb(_emplace_back)(_cx_self* self, i_valraw raw)
                            { return _cx_memb(_push_back)(self, i_valfrom(raw)); }
STC_INLINE void         _cx_memb(_pop_front)(_cx_self* self)
                            { i_valdel(self->data); ++self->data; --cdeq_rep_(self)->size; }
STC_INLINE _cx_value*   _cx_memb(_back)(const _cx_self* self)
                            { return self->data + cdeq_rep_(self)->size - 1; }
STC_INLINE _cx_value*   _cx_memb(_front)(const _cx_self* self) { return self->data; }
STC_INLINE _cx_iter     _cx_memb(_begin)(const _cx_self* self)
                            { return c_make(_cx_iter){self->data}; }
STC_INLINE _cx_iter     _cx_memb(_end)(const _cx_self* self)
                            { return c_make(_cx_iter){self->data + cdeq_rep_(self)->size}; }
STC_INLINE void         _cx_memb(_next)(_cx_iter* it) { ++it->ref; }
STC_INLINE _cx_iter     _cx_memb(_advance)(_cx_iter it, intptr_t offs)
                            { it.ref += offs; return it; }

STC_INLINE _cx_self
_cx_memb(_with_capacity)(size_t n) {
    _cx_self cx = _cx_memb(_init)();
    _cx_memb(_expand_right_half_)(&cx, 0, n);
    return cx;
}

STC_INLINE void
_cx_memb(_shrink_to_fit)(_cx_self *self) {
    if (_cx_memb(_size)(*self) != _cx_memb(_capacity)(*self)) {
        _cx_self cx = _cx_memb(_clone)(*self);
        _cx_memb(_del)(self); *self = cx;
    }
}

#ifndef i_queue

STC_INLINE _cx_value* _cx_memb(_emplace_front)(_cx_self* self, i_valraw raw) {
    return _cx_memb(_push_front)(self, i_valfrom(raw));
}

STC_INLINE void _cx_memb(_pop_back)(_cx_self* self) {
    _cx_value* p = &self->data[--cdeq_rep_(self)->size];
    i_valdel(p);
}

STC_INLINE const _cx_value* _cx_memb(_at)(const _cx_self* self, size_t idx) {
    assert(idx < cdeq_rep_(self)->size); 
    return self->data + idx;
}

STC_INLINE size_t _cx_memb(_index)(_cx_self cx, _cx_iter it) {
    return it.ref - cx.data;
}

STC_INLINE void
_cx_memb(_reserve)(_cx_self* self, size_t n) {
    size_t sz = cdeq_rep_(self)->size;
    if (n > sz) _cx_memb(_expand_right_half_)(self, sz, n - sz);
}

STC_INLINE _cx_iter
_cx_memb(_insert)(_cx_self* self, size_t idx, i_val value) {
    return _cx_memb(_insert_range_p)(self, self->data + idx, &value, &value + 1, false);
}
STC_INLINE _cx_iter
_cx_memb(_insert_n)(_cx_self* self, size_t idx, const _cx_value arr[], size_t n) {
    return _cx_memb(_insert_range_p)(self, self->data + idx, arr, arr + n, false);
}
STC_INLINE _cx_iter
_cx_memb(_insert_at)(_cx_self* self, _cx_iter it, i_val value) {
    return _cx_memb(_insert_range_p)(self, it.ref, &value, &value + 1, false);
}

STC_INLINE _cx_iter
_cx_memb(_emplace)(_cx_self* self, size_t idx, i_valraw raw) {
    return _cx_memb(_emplace_range_p)(self, self->data + idx, &raw, &raw + 1);
}
STC_INLINE _cx_iter
_cx_memb(_emplace_n)(_cx_self* self, size_t idx, const _cx_rawvalue arr[], size_t n) {
    return _cx_memb(_emplace_range_p)(self, self->data + idx, arr, arr + n);
}
STC_INLINE _cx_iter
_cx_memb(_emplace_at)(_cx_self* self, _cx_iter it, i_valraw raw) {
    return _cx_memb(_emplace_range_p)(self, it.ref, &raw, &raw + 1);
}
STC_INLINE _cx_iter
_cx_memb(_emplace_range)(_cx_self* self, _cx_iter it, _cx_iter it1, _cx_iter it2) {
    return _cx_memb(_insert_range_p)(self, it.ref, it1.ref, it2.ref, true);
}

STC_INLINE _cx_iter
_cx_memb(_erase_n)(_cx_self* self, size_t idx, size_t n) {
    return _cx_memb(_erase_range_p)(self, self->data + idx, self->data + idx + n);
}
STC_INLINE _cx_iter
_cx_memb(_erase_at)(_cx_self* self, _cx_iter it) {
    return _cx_memb(_erase_range_p)(self, it.ref, it.ref + 1);
}
STC_INLINE _cx_iter
_cx_memb(_erase_range)(_cx_self* self, _cx_iter it1, _cx_iter it2) {
    return _cx_memb(_erase_range_p)(self, it1.ref, it2.ref);
}

STC_INLINE _cx_iter
_cx_memb(_find)(const _cx_self* self, i_valraw raw) {
    return _cx_memb(_find_in)(_cx_memb(_begin)(self), _cx_memb(_end)(self), raw);
}

STC_INLINE const _cx_value*
_cx_memb(_get)(const _cx_self* self, i_valraw raw) {
    _cx_iter end = _cx_memb(_end)(self);
    _cx_value* val = _cx_memb(_find_in)(_cx_memb(_begin)(self), end, raw).ref;
    return val == end.ref ? NULL : val;
}

STC_INLINE _cx_value*
_cx_memb(_get_mut)(_cx_self* self, i_valraw raw)
    { return (_cx_value *) _cx_memb(_get)(self, raw); }

STC_INLINE void
_cx_memb(_sort_range)(_cx_iter i1, _cx_iter i2,
                int(*_cmp_)(const _cx_value*, const _cx_value*)) {
    qsort(i1.ref, i2.ref - i1.ref, sizeof *i1.ref, (int(*)(const void*, const void*)) _cmp_);
}

STC_INLINE void
_cx_memb(_sort)(_cx_self* self) {
    _cx_memb(_sort_range)(_cx_memb(_begin)(self), _cx_memb(_end)(self), _cx_memb(_value_compare));
}
#endif // i_queue

/* -------------------------- IMPLEMENTATION ------------------------- */
#if !defined(STC_HEADER) || defined(STC_IMPLEMENTATION) || defined(i_imp)

#ifndef CDEQ_H_INCLUDED
static struct cdeq_rep _cdeq_sentinel = {0, 0};
#define _cdeq_nfront(self) ((self)->data - (self)->_base)
#endif

STC_DEF _cx_self
_cx_memb(_init)(void) {
    _cx_value *b = (_cx_value *) _cdeq_sentinel.base;
    return c_make(_cx_self){b, b};
}

STC_DEF void
_cx_memb(_clear)(_cx_self* self) {
    struct cdeq_rep* rep = cdeq_rep_(self);
    if (rep->cap) {
        for (_cx_value *p = self->data, *q = p + rep->size; p != q; ++p)
            i_valdel(p);
        rep->size = 0;
    }
}

STC_DEF void
_cx_memb(_del)(_cx_self* self) {
    _cx_memb(_clear)(self);
    if (cdeq_rep_(self)->cap)
        c_free(cdeq_rep_(self));
}

STC_DEF size_t
_cx_memb(_realloc_)(_cx_self* self, size_t n) {
    struct cdeq_rep* rep = cdeq_rep_(self);
    size_t sz = rep->size, cap = (size_t) (sz*1.7) + n + 7;
    size_t nfront = _cdeq_nfront(self);
    rep = (struct cdeq_rep*) c_realloc(rep->cap ? rep : NULL,
                                       offsetof(struct cdeq_rep, base) + cap*sizeof(i_val));
    rep->size = sz, rep->cap = cap;
    self->_base = (_cx_value *) rep->base;
    self->data = self->_base + nfront;
    return cap;
}

STC_DEF void
_cx_memb(_expand_right_half_)(_cx_self* self, size_t idx, size_t n) {
    struct cdeq_rep* rep = cdeq_rep_(self);
    size_t sz = rep->size, cap = rep->cap;
    size_t nfront = _cdeq_nfront(self), nback = cap - sz - nfront;
    if (nback >= n || sz*1.3 + n > cap && _cx_memb(_realloc_)(self, n)) {
        memmove(self->data + idx + n, self->data + idx, (sz - idx)*sizeof(i_val));
    } else {
#ifdef i_queue
        size_t pos = 0;
#else
        size_t unused = cap - (sz + n);
        size_t pos = (nfront*2 < unused) ? nfront : unused/2;
#endif
        memmove(self->_base + pos, self->data, idx*sizeof(i_val));
        memmove(self->data + pos + idx + n, self->data + idx, (sz - idx)*sizeof(i_val));
        self->data = self->_base + pos;
    }
}

STC_DEF _cx_value*
_cx_memb(_push_back)(_cx_self* self, i_val value) {
    struct cdeq_rep* rep = cdeq_rep_(self);
    if (_cdeq_nfront(self) + rep->size == rep->cap)
        _cx_memb(_expand_right_half_)(self, rep->size, 1);
    _cx_value *v = self->data + cdeq_rep_(self)->size++;
    *v = value; return v;
}

STC_DEF _cx_self
_cx_memb(_clone)(_cx_self cx) {
    size_t sz = cdeq_rep_(&cx)->size;
    _cx_self out = _cx_memb(_with_capacity)(sz);
    cdeq_rep_(&out)->size = sz;
    for (size_t i = 0; i < sz; ++i) out.data[i] = i_valfrom(i_valto(&cx.data[i]));
    return out;
}

#ifndef i_queue

STC_DEF void
_cx_memb(_expand_left_half_)(_cx_self* self, size_t idx, size_t n) {
    struct cdeq_rep* rep = cdeq_rep_(self);
    size_t sz = rep->size, cap = rep->cap;
    size_t nfront = _cdeq_nfront(self), nback = cap - sz - nfront;
    if (nfront >= n) {
        self->data = (_cx_value *) memmove(self->data - n, self->data, idx*sizeof(i_val));
    } else {
        if (sz*1.3 + n > cap) cap = _cx_memb(_realloc_)(self, n);
        size_t unused = cap - (sz + n);
        size_t pos = (nback*2 < unused) ? unused - nback : unused/2;
        memmove(self->_base + pos + idx + n, self->data + idx, (sz - idx)*sizeof(i_val));
        self->data = (_cx_value *) memmove(self->_base + pos, self->data, idx*sizeof(i_val));
    }
}

STC_DEF _cx_value*
_cx_memb(_insert_space_)(_cx_self* self, _cx_value* pos, size_t n) {
    size_t idx = pos - self->data;
    if (idx*2 < cdeq_rep_(self)->size) _cx_memb(_expand_left_half_)(self, idx, n);
    else                               _cx_memb(_expand_right_half_)(self, idx, n);
    if (n) cdeq_rep_(self)->size += n; /* do only if size > 0 */
    return self->data + idx;
}

STC_DEF _cx_value*
_cx_memb(_push_front)(_cx_self* self, i_val value) {
    if (self->data == self->_base)
        _cx_memb(_expand_left_half_)(self, 0, 1);
    else
        --self->data;
    ++cdeq_rep_(self)->size;
    *self->data = value;
    return self->data;
}

STC_DEF _cx_iter
_cx_memb(_insert_range_p)(_cx_self* self, _cx_value* pos,
                         const _cx_value* p1, const _cx_value* p2, bool clone) {
    pos = _cx_memb(_insert_space_)(self, pos, p2 - p1);
    _cx_iter it = {pos};
    if (clone) for (; p1 != p2; ++p1) *pos++ = i_valfrom(i_valto(p1));
    else memcpy(pos, p1, (p2 - p1)*sizeof *p1);
    return it;
}

STC_DEF _cx_iter
_cx_memb(_emplace_range_p)(_cx_self* self, _cx_value* pos, const _cx_rawvalue* p1, const _cx_rawvalue* p2) {
    pos = _cx_memb(_insert_space_)(self, pos, p2 - p1);
    _cx_iter it = {pos};
    for (; p1 != p2; ++p1) *pos++ = i_valfrom(*p1);
    return it;
}

STC_DEF _cx_iter
_cx_memb(_erase_range_p)(_cx_self* self, _cx_value* p1, _cx_value* p2) {
    size_t n = p2 - p1;
    if (n > 0) {
        _cx_value* p = p1, *end = self->data + cdeq_rep_(self)->size;
        for (; p != p2; ++p) i_valdel(p);
        if (p1 == self->data) self->data += n;
        else memmove(p1, p2, (end - p2) * sizeof(i_val));
        cdeq_rep_(self)->size -= n;
    }
    return c_make(_cx_iter){p1};
}

STC_DEF _cx_iter
_cx_memb(_find_in)(_cx_iter i1, _cx_iter i2, i_valraw raw) {
    for (; i1.ref != i2.ref; ++i1.ref) {
        i_valraw r = i_valto(i1.ref);
        if (i_cmp(&raw, &r) == 0) return i1;
    }
    return i2;
}

STC_DEF int
_cx_memb(_value_compare)(const _cx_value* x, const _cx_value* y) {
    i_valraw rx = i_valto(x);
    i_valraw ry = i_valto(y);
    return i_cmp(&rx, &ry);
}

#endif // i_queue
#endif // IMPLEMENTATION
#include "template.h"
#define CDEQ_H_INCLUDED
