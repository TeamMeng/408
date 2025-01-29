const std = @import("std");
const expect = std.testing.expect;

pub const Node = struct {
    data: i32,
    left: ?*Node,
    right: ?*Node,

    pub fn init(data: i32) Node {
        return Node{
            .data = data,
            .left = null,
            .right = null,
        };
    }
};

pub const BinaryTree = struct {
    root: ?*Node,
    count: usize,
    allocator: std.mem.Allocator,

    pub fn init(root: *Node, allocator: std.mem.Allocator) BinaryTree {
        return BinaryTree{
            .root = root,
            .count = 0,
            .allocator = allocator,
        };
    }

    fn deNode(self: *BinaryTree, node: ?*Node) void {
        if (node) |n| {
            self.deNode(n.left);
            self.deNode(n.right);
            self.allocator.destroy(n);
        }
    }

    pub fn deinit(self: *BinaryTree) void {
        self.deNode(self.root);
        self.count = 0;
    }

    pub fn insert(self: *BinaryTree, parent: ?*Node, left: ?*Node, right: ?*Node) void {
        if (parent) |p| {
            p.left = left;
            p.right = right;

            if (left != null) {
                self.count += 1;
            }

            if (right != null) {
                self.count += 1;
            }
        }
    }

    fn inOrder(self: *BinaryTree, node: ?*Node) void {
        if (node) |n| {
            self.inOrder(n.left);
            std.debug.print("{d} ", .{n.data});
            self.inOrder(n.right);
        }
    }

    pub fn inOrderRecur(self: *BinaryTree) void {
        self.inOrder(self.root);
    }

    fn preOrder(self: *BinaryTree, node: ?*Node) void {
        if (node) |n| {
            std.debug.print("{d} ", .{n.data});
            self.preOrder(n.left);
            self.preOrder(n.right);
        }
    }

    pub fn preOrderRecur(self: *BinaryTree) void {
        self.preOrder(self.root);
    }

    fn postOrder(self: *BinaryTree, node: ?*Node) void {
        if (node) |n| {
            self.postOrder(n.left);
            self.postOrder(n.right);
            std.debug.print("{d} ", .{n.data});
        }
    }

    pub fn postOrderRecur(self: *BinaryTree) void {
        self.postOrder(self.root);
    }
};

test "BinaryTreeTest" {
    const allocator = std.testing.allocator;
    const NodeA = try allocator.create(Node);
    NodeA.* = Node.init(1);
    const NodeB = try allocator.create(Node);
    NodeB.* = Node.init(2);
    const NodeC = try allocator.create(Node);
    NodeC.* = Node.init(3);
    const NodeD = try allocator.create(Node);
    NodeD.* = Node.init(4);

    var tree = BinaryTree.init(NodeA, allocator);
    defer tree.deinit();

    tree.insert(NodeA, NodeB, NodeC);
    tree.insert(NodeB, NodeD, null);

    tree.inOrderRecur();
    std.debug.print("\n", .{});
    tree.preOrderRecur();
    std.debug.print("\n", .{});
    tree.postOrderRecur();
}
