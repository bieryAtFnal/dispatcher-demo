/**
 * @file StorageElement.hpp
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DISPATCHERDEMO_INCLUDE_DISPATCHERDEMO_STORAGEELEMENT_HPP_
#define DISPATCHERDEMO_INCLUDE_DISPATCHERDEMO_STORAGEELEMENT_HPP_

#include "dispatcherdemo/StorageKey.hpp"
#include <cstdint>
#include <memory>

namespace dunedaq {

/**
 * @brief comment
 */
struct StorageElement
{
public:
  StorageKey key;
  size_t     data_size;
  uint8_t*   unowned_data_start;
  std::unique_ptr<uint8_t> owned_data_start;

  const uint8_t* getDataStart() const
  {
    if (owned_data_start.get() != nullptr)
    {
      return owned_data_start.get();
    }
    else
    {
      return unowned_data_start;
    }
  }

  size_t getDataSizeBytes() const
  {
    return data_size;
  }
};

} // namespace dunedaq

#endif // DISPATCHERDEMO_INCLUDE_DISPATCHERDEMO_STORAGEELEMENT_HPP_
