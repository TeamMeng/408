pub const seq_list = @import("seqList.zig");
pub const link_list = @import("linkList.zig");

test {
    // 运行所有公开的测试
    @import("std").testing.refAllDecls(@This());
}
