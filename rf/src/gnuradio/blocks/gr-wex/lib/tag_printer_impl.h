/* -*- c++ -*- */
/*
 * Copyright 2019 <+YOU OR YOUR COMPANY+>.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_WEX_TAG_PRINTER_IMPL_H
#define INCLUDED_WEX_TAG_PRINTER_IMPL_H

#include <wex/tag_printer.h>

namespace gr {
namespace wex {

class tag_printer_impl : public tag_printer {
private:
  const std::string tag_name;
  const std::size_t len;
  gr::thread::mutex d_mutex;

public:
  tag_printer_impl(const std::size_t sizeof_stream_item, const std::string& tag_name, const std::size_t len);
  ~tag_printer_impl();

  int work(int noutput_items,
                   gr_vector_const_void_star &input_items,
                   gr_vector_void_star &output_items);
};

} // namespace wex
} // namespace gr

#endif /* INCLUDED_WEX_TAG_PRINTER_IMPL_H */
