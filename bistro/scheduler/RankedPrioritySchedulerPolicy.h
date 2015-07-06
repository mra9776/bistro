#pragma once

#include "bistro/bistro/scheduler/SchedulerPolicy.h"

namespace facebook { namespace bistro {

class RankedPrioritySchedulerPolicy : public SchedulerPolicy {
public:
 int schedule(std::vector<JobWithNodes>& jobs,
              ResourcesByNodeType& resources_by_node,
              TaskRunnerCallback cb) override;
};

}}
