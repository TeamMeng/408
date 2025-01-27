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

pub const LinkedList = struct {
    head: Node,
    length: usize,
    allocator: std.mem.Allocator,

    pub fn init(allocator: std.mem.Allocator) LinkedList {
        return LinkedList{
            .head = .{
                .data = 0,
                .next = null,
            },
            .length = 0,
            .allocator = allocator,
        };
    }

    pub fn deinit(self: *LinkedList) void {
        var current = self.head.next;
        while (current) |node| {
            const next = node.next;
            self.allocator.destroy(node);
            current = next;
        }
        self.head.next = null;
        self.length = 0;
    }

    pub fn insert(self: *LinkedList, index: usize, value: i32) !void {
        if (index > self.length) {
            return error.IndexOutOfBounds;
        }

        var node = try self.allocator.create(Node);
        node.* = Node.init(value);

        if (index == 0) {
            node.next = self.head.next;
            self.head.next = node;
        } else {
            var i: usize = 0;
            var tmp = &self.head;
            while (i < index - 1) : (i += 1) {
                if (tmp.next) |next| {
                    tmp = next;
                }
            }
            node.next = tmp.next;
            tmp.next = node;
        }

        self.length += 1;
    }

    pub fn delete(self: *LinkedList, value: i32) !void {
        var current = &self.head;

        while (current.next) |next| {
            if (next.data == value) {
                current.next = next.next;
                self.allocator.destroy(next);
                self.length -= 1;
                return;
            }
            current = next;
        }
        return error.ValueNotFound;
    }

    pub fn find(self: LinkedList, value: i32) bool {
        var current = &self.head;
        while (current.next) |next| {
            if (next.data == value) {
                return true;
            }
            current = next;
        }
        return false;
    }

    pub fn getLength(self: LinkedList) usize {
        var ans: usize = 0;
        var current = &self.head;
        while (current.next) |next| {
            current = next;
            ans += 1;
        }
        return ans;
    }

    pub fn get(self: LinkedList, index: usize) !i32 {
        if (index > self.length) {
            return error.IndexOutOfBounds;
        }

        var current = &self.head;
        var i: usize = 0;
        while (i < index) : (i += 1) {
            if (current.next) |next| {
                current = next;
            }
            i += 1;
        }

        return current.data;
    }
};

test "LinkedListTest" {
    const allocator = std.testing.allocator;
    var list = LinkedList.init(allocator);
    defer list.deinit();

    try list.insert(0, 1);
    try list.insert(1, 2);
    try list.insert(2, 3);

    try expect(list.getLength() == 3);

    try expect(list.find(1) == true);
    try expect(list.find(4) == false);

    try list.delete(2);
    try expect(list.getLength() == 2);
    try expect(list.find(2) == false);

    try expect(try list.get(1) == 3);
}
