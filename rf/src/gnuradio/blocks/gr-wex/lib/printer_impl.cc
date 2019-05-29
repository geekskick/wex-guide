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

#include "printer_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace wex {

printer::sptr printer::make() {
  return gnuradio::get_initial_sptr(new printer_impl());
}

/*
 * The private constructor
 */
printer_impl::printer_impl()
    : gr::block("printer", gr::io_signature::make(0, 0, 0),
                gr::io_signature::make(0, 0, 0)) {
  message_port_register_in(pmt::mp("pdu"));
  set_msg_handler(pmt::mp("pdu"),
                  boost::bind(&printer_impl::handle_msg, this, _1));
}

/*
 * Our virtual destructor.
 */
printer_impl::~printer_impl() {}

void printer_impl::handle_msg(pmt::pmt_t pdu) {
  std::cout << "Msg received:\n";
  const auto meta = pmt::car(pdu);
  const auto vector = pmt::cdr(pdu);
  const auto len = pmt::blob_length(vector);
  auto offset = std::size_t{0};
  const auto *d = static_cast<const uint8_t *>(
      pmt::uniform_vector_elements(vector, offset));
  for (std::size_t i = 0; i < len; ++i) {
    if (i % 8 == 0) {
      std::cout << " ";
    }
    std::cout << std::to_string(d[i] & 0x01);
  }
  std::cout << std::endl;
}

}; /* namespace wex */
}; /* namespace gr */
