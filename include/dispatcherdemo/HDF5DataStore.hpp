/**
 * @file HDF5DataStore.hpp
 *
 * This is an implementation of the DataStore interface that interacts with
 * HDF5 files on disk.
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DISPATCHERDEMO_INCLUDE_DISPATCHERDEMO_DATASTORE_HPP_
#define DISPATCHERDEMO_INCLUDE_DISPATCHERDEMO_DATASTORE_HPP_

#include "dispatcherdemo/DataStore.hpp"

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

namespace dunedaq {
namespace dispatcherdemo {

/**
 * @brief comment
 */
class HDF5DataStore : public DataStore
{
public:

  /**
   * @brief HDF5DataStore Constructor
   * @param name Name of the HDF5DataStore instance
   */
  HDF5DataStore(const std::string& name, const std::string& directory_path, const std::string& filename_pattern)
    : DataStore(name)
    , directory_path_(directory_path)
    , filename_pattern_(filename_pattern)
  {}

  /**
   * @brief Push a value onto the HDF5DataStore.
   * @param val Value to push (rvalue)
   * @param timeout Timeout for the push operation.
   *
   * This is a pure virtual function.
   * If push takes longer than the timeout, implementations should throw an
   * exception.
   */
  virtual void write(const StorageElement& element) = 0;

  virtual void write(const std::vector<StorageElement>& element) = 0;


  virtual StorageElement read(const StorageKey& key) = 0;

  virtual std::vector<StorageElement> read(const std::vector<StorageKey>& key) = 0;



private:
  HDF5DataStore(const HDF5DataStore&) = delete;
  HDF5DataStore& operator=(const HDF5DataStore&) = delete;
  HDF5DataStore(HDF5DataStore&&) = default;
  HDF5DataStore& operator=(HDF5DataStore&&) = default;

  std::string directory_path_;
  std::string filename_pattern_;
};

} // namespace dispatcherdemo
} // namespace dunedaq

#endif // DISPATCHERDEMO_INCLUDE_DISPATCHERDEMO_DATASTORE_HPP_
