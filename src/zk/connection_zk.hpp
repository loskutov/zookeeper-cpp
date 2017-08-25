#pragma once

#include <zk/config.hpp>

#include <chrono>

#include "connection.hpp"
#include "string_view.hpp"

typedef struct _zhandle zhandle_t;

namespace zk
{

class connection_zk final :
        public connection
{
public:
    explicit connection_zk(string_view               conn_string,
                           std::chrono::milliseconds recv_timeout = std::chrono::milliseconds(10000)
                          );

    virtual ~connection_zk() noexcept;

    virtual void close() override;

    virtual zk::state state() const override;

    virtual future<get_result> get(string_view path) override;

    virtual future<watch_result> watch(string_view path) override;

    virtual future<get_children_result> get_children(string_view path) override;

    virtual future<watch_children_result> watch_children(string_view path) override;

    virtual future<exists_result> exists(string_view path) override;

    virtual future<watch_exists_result> watch_exists(string_view path) override;

    virtual future<create_result> create(string_view     path,
                                         const buffer&   data,
                                         const acl_list& acl,
                                         create_mode     mode
                                        ) override;

    virtual future<set_result> set(string_view path, const buffer& data, version check) override;

    virtual future<void> erase(string_view path, version check) override;

    virtual future<get_acl_result> get_acl(string_view path) const override;

    virtual future<void> set_acl(string_view path, const acl_list& acl, acl_version check) override;

    virtual future<multi_result> commit(multi_op&& txn) override;

    virtual future<void> load_fence() override;

private:
    static void on_session_event_raw(ptr<zhandle_t>  handle,
                                     int             ev_type,
                                     int             state,
                                     ptr<const char> path,
                                     ptr<void>       watcher_ctx
                                    ) noexcept;

private:
    ptr<zhandle_t> _handle;
};

}
