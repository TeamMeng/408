pub const seq_list = @import("seqList.zig");
pub const link_list = @import("linkList.zig");
pub const array_stack = @import("arrayStack.zig");
pub const link_stack = @import("linkStack.zig");
pub const array_queue = @import("arrayQueue.zig");
pub const link_queue = @import("linkQueue.zig");

test {
    // 运行所有公开的测试
    @import("std").testing.refAllDecls(@This());
}
