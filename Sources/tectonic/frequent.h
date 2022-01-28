#pragma once

#define local_data static
#define local_func static

#define DEREF(symbol) (*(symbol))

//Macro expander
#define TEC_EXPANDER_IMPL(ex) #ex
#define TEC_EXPANDER(ex) TEC_EXPANDER_IMPL(ex)