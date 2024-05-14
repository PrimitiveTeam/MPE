#pragma once

#include "MPE/Errors/Error.h"

// Define errors with unique codes, messages, severity, and categories
#define MPE_ERROR_1001 MPE::Error(1001, "General error occurred", MPE::Severity::Error, MPE::Category::SystemInternal)
#define MPE_ERROR_1002 MPE::Error(1002, "System initialization failed", MPE::Severity::Fatal, MPE::Category::SystemInternal)