struct usb_controller_ops {
    void* start;                      // 0x0
    void* stop;                       // 0x4
    void* set_address;                // 0x8
    void* stall_endpoint;             // 0xC
    void* reset_endpoint_data_toggle  // 0x10
    void* is_endpoint_stalled         // 0x14
    void* do_endpoint_io;             // 0x18
    void* activate_endpoint;          // 0x1C
    void* deactivate_endpoint;        // 0x20
    void* abort_endpoint;             // 0x24
    void* do_test_mode;               // 0x28
    void* get_connection_speed        // 0x2C
};
