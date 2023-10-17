#pragma once

#include "common/rc.h"
#include "event/sql_event.h"

class DeleteTableExecutor
{
public:
  DeleteTableExecutor()          = default;
  virtual ~DeleteTableExecutor() = default;

  RC execute(SQLStageEvent *sql_event);
};