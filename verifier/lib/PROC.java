package lib;

import java.io.PrintStream;
import java.lang.reflect.Field;
import java.util.Map;

public class PROC {
	private static String[] args = { "verifier" };

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

	public static void Exit(int status) {
		try {
			Class<?> cls = Class.forName("lib.ARCH");
			cls.getMethod("shutdown").invoke(null);
			out.println("Exit status: " + Integer.toString(status));
		} catch(Exception ex) {
		}
	}

	public static void Assert(boolean cond, String msg) {
		if(!cond) {
			return;
		}
		
		try {
			Class<?> cls = Class.forName("lib.ARCH");
			err.println("Assertion failure: " + msg);
			cls.getMethod("shutdown").invoke(null);
		} catch(Exception ex) {
		}
	}

	public static String Get_Argument(int index) {
		if (index >= 0 && index < args.length) {
			return args[index];
		}
		return "";
	}

	public static int Get_Argument_Count() {
		return args.length;
	}

	public static String Get_Env_Var(String name) {
		return System.getenv().get(name);
	}

	@SuppressWarnings("unchecked")
	public static boolean Set_Env_Var(String name, String value) {
		try {
			Map<String, String> env = System.getenv();
			Class<?> clazz = env.getClass();
			Field field = clazz.getDeclaredField("m");
			field.setAccessible(true);
			env = (Map<String, String>) field.get(env);
			env.put(name, value);
			return true;
		} catch (Exception e) {
			return false;
		}
	}
	
	public static int System(String command) {
		try {
			Runtime runtime = Runtime.getRuntime();
			Process process = runtime.exec(command);
			process.waitFor();
			return process.exitValue();
		} catch (Exception ex) {
			return -1;
		}
	}
}
