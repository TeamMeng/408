const std = @import("std");
const expect = std.testing.expect;

pub const SeqList = struct {
    data: []i32,
    length: usize,
    capacity: usize,
    allocator: std.mem.Allocator,

    pub fn init(allocator: std.mem.Allocator, capacity: usize) !SeqList {
        const data = try allocator.alloc(i32, capacity);
        return SeqList{
            .data = data,
            .length = 0,
            .capacity = capacity,
            .allocator = allocator,
        };
    }

    pub fn deinit(self: *SeqList) void {
        self.allocator.free(self.data);
    }

    pub fn insert(self: *SeqList, index: usize, value: i32) !void {
        if (index > self.length) {
            return error.IndexOutOfBounds;
        }

        if (self.length >= self.capacity) {
            var data = try self.allocator.alloc(i32, self.capacity * 2);
            for (self.data, 0..) |v, i| {
                data[i] = v;
            }

            self.allocator.free(self.data);
            self.data = data;
            self.capacity *= 2;
        }

        var i: usize = self.length;
        while (i > index) : (i -= 1) {
            self.data[i] = self.data[i - 1];
        }
        self.data[index] = value;
        self.length += 1;
    }

    pub fn get(self: SeqList, index: usize) !i32 {
        if (index >= self.length) {
            return error.IndexOutOfBounds;
        }

        return self.data[index];
    }

    pub fn delete(self: *SeqList, index: usize) !void {
        if (index >= self.length) {
            return error.IndexOutOfBounds;
        }

        var i: usize = index;
        while (i < self.length) : (i += 1) {
            self.data[i] = self.data[i + 1];
        }
        self.length -= 1;
    }

    pub fn set(self: *SeqList, index: usize, value: i32) !void {
        if (index >= self.length) {
            return error.IndexOutOfBounds;
        }

        self.data[index] = value;
    }

    pub fn getLength(self: SeqList) usize {
        return self.length;
    }

    pub fn isEmpty(self: SeqList) bool {
        return self.length == 0;
    }
};

test "SeqListTest" {
    const allocator = std.testing.allocator;
    var list = try SeqList.init(allocator, 5);
    defer list.deinit();

    try list.insert(0, 1);
    try list.insert(1, 2);
    try list.insert(2, 3);

    try expect(list.getLength() == 3);

    try list.delete(1);
    try expect(list.getLength() == 2);
    try expect(try list.get(1) == 3);

    try list.set(0, 10);
    try expect(try list.get(0) == 10);

    try expect(!list.isEmpty());
}
