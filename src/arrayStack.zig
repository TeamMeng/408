const std = @import("std");
const expect = std.testing.expect;

pub const ArrayStack = struct {
    top: usize,
    data: []i32,
    length: usize,
    allocator: std.mem.Allocator,

    pub fn init(length: usize, allocator: std.mem.Allocator) !ArrayStack {
        const data = try allocator.alloc(i32, length);
        return ArrayStack{
            .top = 0,
            .data = data,
            .length = length,
            .allocator = allocator,
        };
    }

    pub fn deinit(self: *ArrayStack) void {
        self.allocator.free(self.data);
        self.top = 0;
    }

    pub fn push(self: *ArrayStack, value: i32) !void {
        if (self.top == self.length) {
            return error.IndexOutOfBounds;
        }

        self.top += 1;
        self.data[self.top] = value;
    }

    pub fn pop(self: *ArrayStack) !i32 {
        if (self.top == 0) {
            return error.IndexOutOfBounds;
        }

        const ans = self.data[self.top];
        self.top -= 1;
        return ans;
    }

    pub fn getTop(self: ArrayStack) !i32 {
        if (self.top == 0) {
            return error.IndexOutOfBounds;
        }

        return self.data[self.top];
    }
};

test "ArrayStackTest" {
    const allocator = std.testing.allocator;
    var list = try ArrayStack.init(5, allocator);
    defer list.deinit();

    try list.push(1);
    try list.push(2);
    try list.push(3);
    try list.push(4);

    try expect(try list.pop() == 4);
    try expect(try list.pop() == 3);
    try expect(try list.pop() == 2);
    try expect(try list.pop() == 1);
}
