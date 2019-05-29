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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "tag_printer_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace wex {

tag_printer::sptr tag_printer::make(const std::size_t sizeof_stream_item, 
                                    const std::string& tag_name,
                                    const std::size_t len) {
  return gnuradio::get_initial_sptr(new tag_printer_impl(sizeof_stream_item, tag_name, len));
}

/*
 * The private constructor
 */
tag_printer_impl::tag_printer_impl(const size_t sizeof_stream_item, 
                                   const std::string& tag_name,
                                   const std::size_t len)
    : gr::sync_block("tag_printer", gr::io_signature::make(1, -1, sizeof_stream_item),
                gr::io_signature::make(0, 0, 0)),
      tag_name(tag_name), len(len) {}

/*
 * Our virtual destructor.
 */
tag_printer_impl::~tag_printer_impl() {}

int tag_printer_impl::work(int noutput_items,
                                   gr_vector_const_void_star &input_items,
                                   gr_vector_void_star &output_items) {
  gr::thread::scoped_lock l(d_mutex);

  for (int i = 0; i < input_items.size(); ++i) {
    std::vector<tag_t> tags;
    const auto read = nitems_read(i);
    get_tags_in_range(tags, i, read,
                      read + static_cast<uint64_t>(noutput_items),
                      pmt::mp(tag_name));
    if (tags.size() == 0) { /*std::cout << "No tags called " << tag_name << "
                               found" << std::endl;*/
    } else {
      std::stringstream ss;
      ss << "--------------- Tag Printer -------------------\n";
      for (const auto &tag : tags) {
        ss << "Tag " << pmt::symbol_to_string(tag.key) << " found:\n\t";

        const auto* in = static_cast<const uint8_t*>(input_items[i]);
        for (int y = 0; y < len; ++y) {
          const auto data_byte = static_cast<int>(in[y + tag.offset]);
          if (std::isprint(data_byte)) {
            ss << static_cast<char>(data_byte) << " ";
          } else {
            ss << std::hex << std::showbase << "[" << data_byte << "] "
               << std::dec;
          }
        }
        ss << "\n";
      }
      std::cout << ss.str() << std::endl;
    }
  }

  // Tell runtime system how many output items we produced.
  return noutput_items;
}

} /* namespace wex */
} /* namespace gr */
