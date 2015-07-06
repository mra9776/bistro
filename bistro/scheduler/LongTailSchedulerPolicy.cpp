#include "bistro/bistro/scheduler/LongTailSchedulerPolicy.h"

#include "bistro/bistro/config/Job.h"
#include "bistro/bistro/config/Node.h"
#include "bistro/bistro/scheduler/utils.h"

namespace facebook { namespace bistro {

using namespace std;

int LongTailSchedulerPolicy::schedule(
    vector<JobWithNodes>& jobs,
    ResourcesByNodeType& resources_by_node,
    TaskRunnerCallback cb) {

  sort(jobs.begin(), jobs.end(),
    [](const JobWithNodes& a, const JobWithNodes& b) {
      return a.nodes.size() < b.nodes.size();
    }
  );

  int scheduled_tasks = 0;
  for (auto job_it = jobs.begin(); job_it != jobs.end();) {
    if (job_it->nodes.empty()) {
      job_it = jobs.erase(job_it);
      continue;
    }
    while (!job_it->nodes.empty()) {
      auto node = job_it->nodes.back();
      job_it->nodes.pop_back();
      const auto ret = try_to_schedule(
        resources_by_node,
        node,
        job_it->job,
        cb
      );
      if (ret == TaskRunnerResponse::RanTask) {
        ++scheduled_tasks;
      } else if (ret == TaskRunnerResponse::DoNotRunMoreTasks) {
        return scheduled_tasks;
      }
    }
    ++job_it;
  }
  return scheduled_tasks;
}

}}
