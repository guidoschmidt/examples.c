const std = @import("std");
const debug = std.debug;
const fs = std.fs;
const log = std.log;
const io = std.io;

fn createExecutable(b: *std.Build, source: []u8, name: []const u8) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});
    const exe = b.addExecutable(.{ .name = name, .optimize = optimize, .target = target, .link_libc = true });
    exe.addCSourceFile(.{ .file = b.path(source) });
    exe.linkLibC();

    b.installArtifact(exe);

    const run_artifact = b.addRunArtifact(exe);
    run_artifact.step.dependOn(b.getInstallStep());
    const run_step = b.step("run", "Run the selection");
    run_step.dependOn(&run_artifact.step);
}

pub fn build(b: *std.Build) !void {
    const src_dir = try fs.cwd().openDir("./src", .{});
    var it = src_dir.iterate();
    var i: u32 = 0;
    while (try it.next()) |path| : (i += 1) {
        debug.print("- {d} {s}\n", .{ i, path.name });
    }

    const in = io.getStdIn();
    var buf = io.bufferedReader(in.reader());

    // Get the Reader interface from BufferedReader
    var r = buf.reader();

    debug.print("\nSelect: ", .{});
    // Ideally we would want to issue more than one read
    // otherwise there is no point in buffering.
    var msg_buf: [4096]u8 = undefined;
    const input = try r.readUntilDelimiterOrEof(&msg_buf, '\n');

    if (input) |input_txt| {
        const parsed_num = try std.fmt.parseInt(usize, input_txt[0..], 10);

        it.reset();
        var j: u32 = 0;
        while (j < parsed_num) : (j += 1) {
            _ = try it.next();
        }
        const selected_example = try it.next();
        debug.print("\nSelected {s}\n", .{selected_example.?.name});

        const source = selected_example.?.name;
        var split_it = std.mem.splitSequence(u8, source, ".");
        const source_name = split_it.next() orelse "none";
        const source_file = try std.fmt.allocPrint(b.allocator, "./src/{s}", .{source});
        defer b.allocator.free(source_file);

        try createExecutable(b, source_file, source_name);
    }
}
