/**
 * @file DataPackager.cpp DataPackager class implementation
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "CommonIssues.hpp"
#include "DataPackager.hpp"

#include <ers/ers.h>
#include <TRACE/trace.h>

#include <chrono>
#include <cstdlib>
#include <thread>

/**
 * @brief Name used by TRACE TLOG calls from this source file
 */
#define TRACE_NAME "DataPackager"   // NOLINT
#define TLVL_ENTER_EXIT_METHODS 10  // NOLINT
#define TLVL_WORK_LOOP 15           // NOLINT

namespace dunedaq {
namespace dispatcherdemo {

DataPackager::DataPackager(const std::string& name)
  : dunedaq::appfwk::DAQModule(name)
  , thread_(std::bind(&DataPackager::do_work, this, std::placeholders::_1))
    //, outputQueues_()
    //, queueTimeout_(100)
{
  register_command("configure", &DataPackager::do_configure);
  register_command("start",  &DataPackager::do_start);
  register_command("stop",  &DataPackager::do_stop);
  register_command("unconfigure",  &DataPackager::do_unconfigure);
}

void DataPackager::init()
{
  TLOG(TLVL_ENTER_EXIT_METHODS) << get_name() << ": Entering init() method";
  TLOG(TLVL_ENTER_EXIT_METHODS) << get_name() << ": Exiting init() method";
}

void
DataPackager::do_configure(const std::vector<std::string>& /*args*/)
{
  TLOG(TLVL_ENTER_EXIT_METHODS) << get_name() << ": Entering do_configure() method";
  waitBetweenSendsMsec_ = get_config().value<size_t>("waitBetweenSendsMsec", static_cast<size_t>(REASONABLE_DEFAULT_MSECBETWEENSENDS));
  TLOG(TLVL_ENTER_EXIT_METHODS) << get_name() << ": Exiting do_configure() method";
}

void
DataPackager::do_start(const std::vector<std::string>& /*args*/)
{
  TLOG(TLVL_ENTER_EXIT_METHODS) << get_name() << ": Entering do_start() method";
  thread_.start_working_thread();
  ERS_LOG(get_name() << " successfully started");
  TLOG(TLVL_ENTER_EXIT_METHODS) << get_name() << ": Exiting do_start() method";
}

void
DataPackager::do_stop(const std::vector<std::string>& /*args*/)
{
  TLOG(TLVL_ENTER_EXIT_METHODS) << get_name() << ": Entering do_stop() method";
  thread_.stop_working_thread();
  ERS_LOG(get_name() << " successfully stopped");
  TLOG(TLVL_ENTER_EXIT_METHODS) << get_name() << ": Exiting do_stop() method";
}

void
DataPackager::do_unconfigure(const std::vector<std::string>& /*args*/)
{
  TLOG(TLVL_ENTER_EXIT_METHODS) << get_name() << ": Entering do_unconfigure() method";
  waitBetweenSendsMsec_ = REASONABLE_DEFAULT_MSECBETWEENSENDS;
  TLOG(TLVL_ENTER_EXIT_METHODS) << get_name() << ": Exiting do_unconfigure() method";
}

void
DataPackager::do_work(std::atomic<bool>& running_flag)
{
  TLOG(TLVL_ENTER_EXIT_METHODS) << get_name() << ": Entering do_work() method";
  size_t loopCount = 0;

  while (running_flag.load()) {
    TLOG(TLVL_WORK_LOOP) << get_name() << ": Start of work loop";
    ++loopCount;

    TLOG(TLVL_WORK_LOOP) << get_name() << ": Start of sleep between sends";
    std::this_thread::sleep_for(std::chrono::milliseconds(waitBetweenSendsMsec_));
    TLOG(TLVL_WORK_LOOP) << get_name() << ": End of do_work loop";
  }

  std::ostringstream oss_summ;
  oss_summ << ": Exiting the do_work() method after " << loopCount << " loops.";
  ers::info(ProgressUpdate(ERS_HERE, get_name(), oss_summ.str()));
  TLOG(TLVL_ENTER_EXIT_METHODS) << get_name() << ": Exiting do_work() method";
}

} // namespace dispatcherdemo 
} // namespace dunedaq

DEFINE_DUNE_DAQ_MODULE(dunedaq::dispatcherdemo::DataPackager)
