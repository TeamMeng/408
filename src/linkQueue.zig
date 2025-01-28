const std = @import("std");
const expect = std.testing.expect;

pub const Node = struct {
    data: i32,
    next: ?*Node,

    fn init(data: i32) Node {
        return Node{
            .data = data,
            .next = null,
        };
    }
};

pub const LinkQueue = struct {
    front: ?*Node,
    rear: ?*Node,
    length: usize,
    allocator: std.mem.Allocator,

    pub fn init(allocator: std.mem.Allocator) LinkQueue {
        return LinkQueue{
            .front = null,
            .rear = null,
            .length = 0,
            .allocator = allocator,
        };
    }

    pub fn deinit(self: *LinkQueue) void {
        var cur = self.front;
        while (cur) |node| {
            const next = node.next;
            self.allocator.destroy(node);
            cur = next;
        }
        self.front = null;
        self.rear = null;
        self.length = 0;
    }

    pub fn push(self: *LinkQueue, data: i32) !void {
        const node = try self.allocator.create(Node);
        node.* = Node.init(data);

        if (self.rear) |rear| {
            rear.next = node;
            self.rear = node;
        } else {
            self.front = node;
            self.rear = node;
        }

        self.length += 1;
    }

    pub fn pop(self: *LinkQueue) !i32 {
        if (self.front) |front| {
            const ans = front.data;

            const next = front.next;
            self.allocator.destroy(front);
            self.front = next;
            if (self.front == null) {
                self.rear = null;
            }
            self.length -= 1;

            return ans;
        } else {
            return error.EmptyQueue;
        }
    }
};

test "LinkQueueTest" {
    const allocator = std.testing.allocator;
    var queue = LinkQueue.init(allocator);
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
