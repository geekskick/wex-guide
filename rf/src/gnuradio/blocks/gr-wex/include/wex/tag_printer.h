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


#ifndef INCLUDED_WEX_TAG_PRINTER_H
#define INCLUDED_WEX_TAG_PRINTER_H

#include <wex/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace wex {

    /*!
     * \brief Prints a number of bytes following the tag
     * \ingroup wex
     *
     */
    class WEX_API tag_printer : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<tag_printer> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of wex::tag_printer.
       *
       * To avoid accidental use of raw pointers, wex::tag_printer's
       * constructor is in a private implementation
       * class. wex::tag_printer::make is the public interface for
       * creating new instances.
       */
      static sptr make(const std::size_t sizeof_stream_item, const std::string& tag_name, const std::size_t len);
    };

  } // namespace wex
} // namespace gr

#endif /* INCLUDED_WEX_TAG_PRINTER_H */

