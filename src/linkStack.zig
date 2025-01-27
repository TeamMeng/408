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

pub const LinkStack = struct {
    top: Node,
    length: usize,
    allocator: std.mem.Allocator,

    pub fn init(allocator: std.mem.Allocator) LinkStack {
        return LinkStack{
            .top = .{ .data = 0, .next = null },
            .length = 0,
            .allocator = allocator,
        };
    }

    pub fn deinit(self: *LinkStack) void {
        var cur = &self.top;
        while (cur.next) |next| {
            self.allocator.destroy(cur);
            cur = next;
        }
        self.length = 0;
    }

    pub fn push(self: *LinkStack, data: i32) !void {
        var node = try self.allocator.create(Node);

        node.* = Node.init(data);

        node.next = self.top.next;
        self.top.next = node;
        self.length += 1;
    }

    pub fn pop(self: *LinkStack) !i32 {
        var cur = &self.top;
        if (cur.next) |next| {
            const ans = next.data;
            cur.next = next.next;
            self.allocator.destroy(next);
            self.length -= 1;
            return ans;
        } else {
            return error.OutOfMemory;
        }
    }
};

test "LinkStackText" {
    const allocator = std.testing.allocator;
    var stack = LinkStack.init(allocator);
    defer stack.deinit();

    try stack.push(1);
    try stack.push(2);
    try stack.push(3);

    try expect(try stack.pop() == 3);
    try expect(try stack.pop() == 2);
    try expect(try stack.pop() == 1);
}
