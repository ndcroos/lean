/*
Copyright (c) 2017 Microsoft Corporation. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.

Author: Jared Roesch
*/
#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include "library/handle.h"
#include "util/buffer.h"
#include "library/pipe.h"

namespace lean  {

enum stdio {
    INHERIT,
    PIPED,
    NUL,
};

struct child {
    virtual ~child() {};
    virtual handle_ref get_stdin() = 0;
    virtual handle_ref get_stdout() = 0;
    virtual handle_ref get_stderr() = 0;
    virtual unsigned wait() = 0;
};

class process {
    std::string m_proc_name;
    buffer<std::string> m_args;
    optional<stdio> m_stdout;
    optional<stdio> m_stdin;
    optional<stdio> m_stderr;
    optional<std::string> m_cwd;
    std::unordered_map<std::string, optional<std::string>> m_env;
public:
    process(process const & proc) = default;
    process(std::string exe_name);
    process & arg(std::string arg_str);
    process & set_stdin(stdio cfg);
    process & set_stdout(stdio cfg);
    process & set_stderr(stdio cfg);
    process & set_cwd(std::string const & cwd);
    process & set_env(std::string const & var, optional<std::string> const & val);
    std::shared_ptr<child> spawn();
    void run();
};
}
