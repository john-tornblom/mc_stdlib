package lib;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileDescriptor;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URISyntaxException;
import java.net.URL;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.HashMap;
import java.util.Map;

public class FS {

	private static Map<Integer, FileDescriptor> fdMap;

	static {
		fdMap = new HashMap<Integer, FileDescriptor>();
		fdMap.put(0, FileDescriptor.in);
		fdMap.put(1, FileDescriptor.out);
		fdMap.put(2, FileDescriptor.err);
	}

	public static boolean Close(String fdStr) {
		return Close(Integer.parseInt(fdStr));
	}

	public static synchronized boolean Close(int fdInt) {
		if (fdInt < 3) {
			return false;
		}
		if (!fdMap.containsKey(fdInt)) {
			return false;
		}

		FileDescriptor fd = fdMap.remove(fdInt);
		if (!fd.valid()) {
			return false;
		}

		try {
			FileInputStream fis = new FileInputStream(fd);
			fis.close();
			return true;
		} catch (IOException e) {
			return false;
		}
	}

	@SuppressWarnings("resource")
	public static synchronized int Open(String filename, String mode) {
		int fdInt = fdMap.size();

		try {
			filename = getAbsolutePath(filename);
			if ("File_Mode::Read".equals(mode)) {
				FileInputStream fis = new FileInputStream(filename);
				fdMap.put(fdInt, fis.getFD());
			} else {
				boolean append = "File_Mode::Append".equals(mode);
				FileOutputStream fos = new FileOutputStream(filename, append);
				fdMap.put(fdInt, fos.getFD());
			}
		} catch (Exception ex) {
			return -1;
		}
		return fdInt;
	}

	public static String Read(String fdStr, int length) {
		return Read(Integer.parseInt(fdStr), length);
	}

	@SuppressWarnings("resource")
	public static synchronized String Read(int fdInt, int length) {
		if (!fdMap.containsKey(fdInt)) {
			return "";
		}

		FileDescriptor fd = fdMap.get(fdInt);
		FileInputStream fis = new FileInputStream(fd);

		try {
			if (length <= 0) {
				length = (int) fis.getChannel().size();
			}
			byte[] b = new byte[length];
			fis.read(b);
			return new String(b);
		} catch (IOException e) {
			return "";
		}
	}

	public static String Read_Line(String fdStr) {
		return Read_Line(Integer.parseInt(fdStr));
	}

	@SuppressWarnings("resource")
	public static synchronized String Read_Line(int fdInt) {
		if (!fdMap.containsKey(fdInt)) {
			return "";
		}

		FileDescriptor fd = fdMap.get(fdInt);
		FileInputStream fis = new FileInputStream(fd);
		InputStreamReader isr = new InputStreamReader(fis);
		BufferedReader br = new BufferedReader(isr);

		try {
			return br.readLine();
		} catch (IOException e) {
			return "";
		}
	}

	public static boolean Remove(String filename) {
		try {
			filename = getAbsolutePath(filename);
			Path path = FileSystems.getDefault().getPath(filename);
			Files.delete(path);
			return true;
		} catch (Exception e) {
			return false;
		}
	}

	public static boolean Write(String fdStr, String str) {
		return Write(Integer.parseInt(fdStr), str);
	}

	public static synchronized boolean Write(int fdInt, String str) {
		if (!fdMap.containsKey(fdInt)) {
			return false;
		}

		FileDescriptor fd = fdMap.get(fdInt);
		@SuppressWarnings("resource")
		FileOutputStream fos = new FileOutputStream(fd);

		try {
			fos.write(str.getBytes());
			return true;
		} catch (IOException e) {
			return false;
		}
	}

	public static boolean Write_Line(int fdInt, String str) {
		return Write(fdInt, str + "\n");
	}

	public static boolean Write_Line(String fdStr, String str) {
		return Write(fdStr, str + "\n");
	}

	public static String Mk_Temp(String prefix, String suffix) {
		try {
			return Files.createTempFile(prefix, suffix).toString();
		} catch (Exception e) {
			return "";
		}
	}
	
	public static boolean Exists(String filename) {
		try {
			filename = getAbsolutePath(filename);
			Path path = FileSystems.getDefault().getPath(filename);
			return Files.exists(path);
		} catch (Exception e) {
			return false;
		}
	}

	private static String getAbsolutePath(String filename) throws MalformedURLException, URISyntaxException {
		File file = new File(filename);
		if (!file.isAbsolute()) {
			URL url = new URL(System.getProperty("osgi.instance.area"));
			file = new File(url.toURI());
			file = new File(file, filename);
		}

		return file.getPath();
	}
}
