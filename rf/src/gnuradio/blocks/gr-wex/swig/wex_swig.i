/* -*- c++ -*- */

#define WEX_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "wex_swig_doc.i"

%{
#include "wex/printer.h"
#include "wex/tag_printer.h"
%}


%include "wex/printer.h"
GR_SWIG_BLOCK_MAGIC2(wex, printer);
%include "wex/tag_printer.h"
GR_SWIG_BLOCK_MAGIC2(wex, tag_printer);
