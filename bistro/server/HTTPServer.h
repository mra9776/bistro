#pragma once

#include <boost/asio.hpp>
#include <memory>
#include <set>

#include "bistro/bistro/server/Connection.h"

namespace facebook { namespace bistro {

/**
 * A very simple HTTP server. Exists to support the Bistro HTTP monitor. Not
 * appropriate for critical or high volume workloads, or for use with external
 * clients. Not fully standards compliant.
 */
class HTTPServer {

public:
  HTTPServer(int port, const std::string&, RequestProcessor process_callback);
  void run();

private:
  void accept();

  RequestProcessor processCallback_;

  boost::asio::io_service ioService_;
  boost::asio::ip::tcp::acceptor acceptor_;
  boost::asio::ip::tcp::socket socket_;

  std::set<ConnectionPtr> connections_;


};

}}
