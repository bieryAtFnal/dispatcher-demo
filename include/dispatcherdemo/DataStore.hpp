/**
 * @file DataStore.hpp
 *
 * This is the interface for Data Storage systems.
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DISPATCHERDEMO_INCLUDE_DISPATCHERDEMO_DATASTORE_HPP_
#define DISPATCHERDEMO_INCLUDE_DISPATCHERDEMO_DATASTORE_HPP_

#include "appfwk/NamedObject.hpp"

#include <ers/Issue.h>

#include <chrono>
#include <cstddef>
#include <memory>
#include <string>
#include <vector>

namespace dunedaq {
namespace dispatcherdemo {

/**
 * @brief comment
 */
class DataStore : public NamedObject
{
public:

  /**
   * @brief DataStore Constructor
   * @param name Name of the DataStore instance
   */
  explicit DataStore(const std::string& name)
    : NamedObject(name)
  {}

  /**
   * @brief Writes the specified data payload into the DataStore.
   * @param element Data element to write.
   */
  virtual void write(const StorageElement& element) = 0;

  //virtual void write(const std::vector<StorageElement>& element) = 0;

  //virtual StorageElement read(const StorageKey& key) = 0;

  //virtual std::vector<StorageElement> read(const std::vector<StorageKey>& key) = 0;

private:
  DataStore(const DataStore&) = delete;
  DataStore& operator=(const DataStore&) = delete;
  DataStore(DataStore&&) = default;
  DataStore& operator=(DataStore&&) = default;
};

} // namespace dispatcherdemo
} // namespace dunedaq

#endif // DISPATCHERDEMO_INCLUDE_DISPATCHERDEMO_DATASTORE_HPP_
