/**
 * @file StorageKey.hpp
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DISPATCHERDEMO_INCLUDE_DISPATCHERDEMO_STORAGEKEY_HPP_
#define DISPATCHERDEMO_INCLUDE_DISPATCHERDEMO_STORAGEKEY_HPP_

#include <cstdint>
#include <string>

namespace dunedaq {

/**
 * @brief comment
 */
struct StorageKey
{
public:
  uint32_t run;
  std::string record_identifier;  // trigger number or timeslice ID
  std::string subdet_name;
  uint16_t apa_number;
  uint16_t link_number;

  // will we want isValid() methods for the fields?
};

} // namespace dunedaq

#endif // DISPATCHERDEMO_INCLUDE_DISPATCHERDEMO_STORAGEKEY_HPP_
