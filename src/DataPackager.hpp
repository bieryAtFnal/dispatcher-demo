/**
 * @file DataPackager.hpp
 *
 * DataPackager is a simple DAQModule implementation that
 * reads data fragments and writes them back out as a unit.
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DISPATCHERDEMO_SRC_DATAPACKAGER_HPP_
#define DISPATCHERDEMO_SRC_DATAPACKAGER_HPP_

#include "appfwk/DAQModule.hpp"
//#include "appfwk/DAQSink.hpp"
#include "appfwk/ThreadHelper.hpp"

#include <ers/Issue.h>

#include <memory>
#include <string>
//#include <vector>

namespace dunedaq {
namespace dispatcherdemo {

/**
 * @brief DataPackager reads data in, packages it appropriately for
 * transfer to offline, then writes it back out.
 */
class DataPackager : public dunedaq::appfwk::DAQModule
{
public:
  /**
   * @brief DataPackager Constructor
   * @param name Instance name for this DataPackager instance
   */
  explicit DataPackager(const std::string& name);

  DataPackager(const DataPackager&) =
    delete; ///< DataPackager is not copy-constructible
  DataPackager& operator=(const DataPackager&) =
    delete; ///< DataPackager is not copy-assignable
  DataPackager(DataPackager&&) =
    delete; ///< DataPackager is not move-constructible
  DataPackager& operator=(DataPackager&&) =
    delete; ///< DataPackager is not move-assignable

  void init() override;

private:
  // Commands
  void do_configure(const std::vector<std::string>& args);
  void do_start(const std::vector<std::string>& args);
  void do_stop(const std::vector<std::string>& args);
  void do_unconfigure(const std::vector<std::string>& args);

  // Threading
  dunedaq::appfwk::ThreadHelper thread_;
  void do_work(std::atomic<bool>&);

  // Configuration defaults
  //const size_t REASONABLE_DEFAULT_INTSPERLIST = 4;
  const size_t REASONABLE_DEFAULT_MSECBETWEENSENDS = 1000;

  // Configuration
  //std::vector<std::unique_ptr<dunedaq::appfwk::DAQSink<std::vector<int>>>> outputQueues_;
  //std::chrono::milliseconds queueTimeout_;
  //size_t nIntsPerList_ = REASONABLE_DEFAULT_INTSPERLIST;
  size_t waitBetweenSendsMsec_ = REASONABLE_DEFAULT_MSECBETWEENSENDS;
};
} // namespace dispatcherdemo

ERS_DECLARE_ISSUE_BASE(dispatcherdemo,
                       NoOutputQueuesAvailableWarning,
                       appfwk::GeneralDAQModuleIssue,
                       "No output queues were available, so the generated list of integers will be dropped. Has initialization been successfully completed?",
                       ((std::string)name),
                       ERS_EMPTY)

} // namespace dunedaq

#endif // DISPATCHERDEMO_SRC_DATAPACKAGER_HPP_
