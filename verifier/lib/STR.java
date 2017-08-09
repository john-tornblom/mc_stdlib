package lib;

import java.util.UUID;

public class STR {

	public static String From_ASCII_Code(int value) {
		if (value <= 0) {
			return "";
		}
		
		if (value >= 128) {
			return "";
		}
		try {
			return String.valueOf(Character.toChars(value));
		} catch (Exception ex) {
			return "";
		}
	}

	public static String From_Boolean(boolean value) {
		return new Boolean(value).toString();
	}

	public static String From_Integer(int value) {
		return new Integer(value).toString();
	}

	public static String From_Real(float value) {
		return new Float(value).toString();
	}

	public static String From_Unique_Id(UUID value) {
		return value.toString();
	}

	public static int Index(String str, String sub, int start) {
		return str.indexOf(sub, start);
	}

	public static boolean Contains(String str, String sub) {
		return str.contains(sub);
	}
	
	public static int Length(String str) {
		return str.length();
	}

	public static String Replace(String str, String old, String new_) {
		try {
			return str.replace(old, new_);
		} catch (Exception ex) {
			return str;
		}
	}

	public static String Substring(String str, int start, int end) {
		try {
			return str.substring(start, end);
		} catch (Exception ex) {
			return "";
		}
	}
	
	public static int To_ASCII_Code(String str, int index) {
		try {
			return str.charAt(index);
		} catch (Exception ex) {
			return 0;
		}
	}
	
	public static boolean To_Boolean(String str) {
		try {
			return "true".equals(str.toLowerCase());
		} catch (Exception ex) {
			return false;
		}
	}

	public static int To_Integer(String str) {
		try {
			return Integer.decode(str.toUpperCase());
		} catch (Exception ex) {
			return 0;
		}
	}

	public static float To_Real(String str) {
		try {
			return Float.parseFloat(str);
		} catch (Exception ex) {
			return 0;
		}
	}

	public static UUID To_Unique_Id(String str) {
		try {
			return UUID.fromString(str);
		} catch (Exception ex) {
			return UUID.fromString("00000000-0000-0000-0000-000000000000");
		}
	}
}
