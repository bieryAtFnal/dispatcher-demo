/**
 * @file DataStoreSink.hpp DataStoreSink class interface
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DISPATCHERDEMO_INCLUDE_DISPATCHERDEMO_DATASTORESINK_HPP_
#define DISPATCHERDEMO_INCLUDE_DISPATCHERDEMO_DATASTORESINK_HPP_

#include "dispatcherdemo/DataStore.hpp"

#include "TRACE/trace.h"
#include "ers/Issue.h"

#include <memory>
#include <string>
#include <utility>

namespace dunedaq {
namespace dispatcherdemo {

class DataStoreSink : public Named
{
public:
  //explicit DataStoreSink(const std::string& name);
  explicit DataStoreSink(std::shared_ptr<DataStore> data_store)
    : data_store_(data_store)
  {}
  // 31-Aug-2020, KAB: I fully expect the way that we construct DataStore instances
  // to change; this is just a placeholder.

  void write(const StorageElement& element)
  {
    data_store_->write(element);
  }
  //void write(const std::vector<StorageElement>& elements);

  const std::string& get_name() const final {return data_store_->get_name(); }

private:
  std::shared_ptr<DataStore> data_store_;
};

} // namespace dispatcherdemo
} // namespace dunedaq

#endif // DISPATCHERDEMO_INCLUDE_DISPATCHERDEMO_DATASTORESINK_HPP_
