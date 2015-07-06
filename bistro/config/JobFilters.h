#pragma once

#include <boost/operators.hpp>
#include <boost/regex.hpp>
#include <functional>
#include <string>
#include <unordered_set>

#include "folly/dynamic.h"
#include "folly/Hash.h"

namespace facebook { namespace bistro {

class Node;

class JobFilters : boost::equality_comparable<JobFilters> {

public:
  JobFilters();
  explicit JobFilters(const folly::dynamic& d);

  JobFilters(JobFilters&&) = default;
  JobFilters(const JobFilters&) = default;
  JobFilters& operator=(JobFilters&&) = default;
  JobFilters& operator=(const JobFilters&) = default;

  /**
   * Check if a Node passes these filters.
   */
  bool doesPass(const std::string& salt, const Node& n) const;

  /**
   * Check if a string passes these filters. Unlike the overload above this does
   * not check the tag whitelist.
   */
  bool doesPass(const std::string& salt, const std::string& s) const;

  bool isEmpty() const;

  folly::dynamic toDynamic() const;

  bool operator==(const JobFilters&) const;

private:
  std::unordered_set<std::string> whitelist_;
  boost::regex whitelistRegex_;
  std::unordered_set<std::string> blacklist_;
  boost::regex blacklistRegex_;
  std::unordered_set<std::string> tagWhitelist_;
  double fractionOfNodes_;
  size_t fractionCutoff_;
  bool isEmpty_;
  std::hash<std::pair<std::string, std::string>> hasher_;

  void setFractionOfNodes(double fraction);
  bool isNonTriviallyEmpty() const;

};

}}
