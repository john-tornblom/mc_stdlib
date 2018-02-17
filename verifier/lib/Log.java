package lib;

import java.io.PrintStream;

public class Log {

	private static int level = 4; // Notice
	private static int fd = 1;
	private static PrintStream out = null;
	private static PrintStream err = null;

	static {
		try {
			Class<?> cls = Class.forName("org.xtuml.bp.core.CorePlugin");
			out = (PrintStream) cls.getField("out").get(null);
			err = (PrintStream) cls.getField("err").get(null);
		} catch (Throwable t) {
			out = System.out;
			err = System.err;
		}
	}

	private static synchronized void Log_out(String msg) {
		if (fd <= 2)
			out.println(msg);
		else
			FS.Write_Line(fd, msg);
	}

	private static synchronized void Log_err(String msg) {
		if (fd <= 2)
			err.println(msg);
		else
			FS.Write_Line(fd, msg);
	}

	public static synchronized void Configure(String fdStr, String levelStr) {
		fd = Integer.parseInt(fdStr);

		if ("Log_Level::Debug".equals(levelStr))
			level = 6;

		else if ("Log_Level::Info".equals(levelStr))
			level = 5;

		else if ("Log_Level::Notice".equals(levelStr))
			level = 4;

		else if ("Log_Level::Warning".equals(levelStr))
			level = 3;

		else if ("Log_Level::Error".equals(levelStr))
			level = 2;

		else if ("Log_Level::Critical".equals(levelStr))
			level = 1;

		else if ("Log_Level::Fatal".equals(levelStr))
			level = 0;

		else if ("Log_Level::Silent".equals(levelStr))
			level = -1;

		else
			err.println("ERROR: Unknown logging level " + levelStr);
	}

	public static void Fatal(String msg) {
		if (level >= 0)
			Log_err("FATAL: " + msg);
	}

	public static void Critical(String msg) {
		if (level >= 1)
			Log_err("CRITICAL: " + msg);
	}

	public static void Error(String msg) {
		if (level >= 2)
			Log_err("ERROR: " + msg);
	}

	public static void Warning(String msg) {
		if (level >= 3)
			Log_err("WARNING: " + msg);
	}

	public static void Notice(String msg) {
		if (level >= 4)
			Log_out("NOTICE: " + msg);
	}

	public static void Info(String msg) {
		if (level >= 5)
			Log_out("INFO: " + msg);
	}

	public static void Debug(String msg) {
		if (level >= 6)
			Log_out("DEBUG: " + msg);
	}
}
