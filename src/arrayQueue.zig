const std = @import("std");
const expect = std.testing.expect;

pub const ArrayQueue = struct {
    front: usize,
    rear: usize,
    data: []i32,
    length: usize,
    allocator: std.mem.Allocator,

    pub fn init(length: usize, allocator: std.mem.Allocator) !ArrayQueue {
        const data = try allocator.alloc(i32, length);
        return ArrayQueue{ .front = 0, .rear = 0, .data = data, .length = length, .allocator = allocator };
    }

    pub fn deinit(self: *ArrayQueue) void {
        self.allocator.free(self.data);
        self.length = 0;
        self.front = 0;
        self.rear = 0;
    }

    pub fn push(self: *ArrayQueue, value: i32) !void {
        if ((self.rear + 1) % self.length == self.front) {
            return error.IndexOutOfBounds;
        }

        self.rear = (self.rear + 1) % self.length;
        self.data[self.rear] = value;
    }

    pub fn pop(self: *ArrayQueue) !i32 {
        if (self.front == self.rear) {
            return error.IndexOutOfBounds;
        }

        self.front = (self.front + 1) % self.length;
        return self.data[self.front];
    }
};

test "ArrayQueueTest" {
    const allocator = std.testing.allocator;
    var queue = try ArrayQueue.init(5, allocator);
    defer queue.deinit();
    try queue.push(1);
    try queue.push(2);
    try queue.push(3);
    try queue.push(4);

    try expect(try queue.pop() == 1);
    try expect(try queue.pop() == 2);
    try expect(try queue.pop() == 3);
    try expect(try queue.pop() == 4);
}
