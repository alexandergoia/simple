import javax.swing.*;

import java.awt.*;
import java.awt.event.*;
import java.awt.print.*;

import java.io.*;
import java.net.*;

import java.util.*;

class textfinger implements Printable, ActionListener
{

	JFrame     frame;
	JTextField textfield;
	JButton	   button;
	JTextArea  textarea;
	JButton    printbutton;

	String     site;
	String	   finger_string;
	int	   success;

	textfinger()
	{
		frame = new JFrame("Finger client for Windows");
		frame.setSize(600, 200);
		
		textfield = new JTextField();
		textfield.setBounds(100, 50, 250, 30);

		button = new JButton("Finger me !");
		button.setBounds(450, 50, 100, 30);		

		button.addActionListener(this);
		frame.add(textfield);
		frame.add(button);

		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setLayout(null);
		frame.setVisible(true);
	}

	public int networking()
	{
		int net_success = 0;
		finger_string = "";
		String line;

		try {
		Socket finger_socket = new Socket(site, 7900);
		BufferedReader inp = new BufferedReader(
			(new InputStreamReader
			(finger_socket.getInputStream())));
		
		finger_socket.getOutputStream().write(0);
		line = inp.readLine();
		
		while(line != null) {
			// System.out.println(line);
			finger_string += line;
			finger_string += "\n";
			line = inp.readLine();
			}

		finger_socket.close();
		}

		catch(UnknownHostException e) { net_success = 1; }
		catch(IOException e) { net_success = 1; }
		
		return net_success;
	}

	public void printing_on_screen()
	{
		frame.setSize(600, 800);
		
		textarea.setText(finger_string);

		textarea.setBounds(10, 150, 550, 550);
		textarea.setEditable(false);
		
		frame.add(textarea);

		printbutton = new JButton("Print me !");
		printbutton.setBounds(250, 720, 100, 30);
		printbutton.addActionListener(this);

		frame.add(printbutton);

		frame.setVisible(true);

		// System.out.println(finger_string);
		// finger_string to null;
	}

	public void printing_on_paper()
	{
		PrinterJob job = PrinterJob.getPrinterJob();
		job.setPrintable(this);
		try { job.print(); }
		catch (PrinterException ex) {};
	}

	public int print(Graphics g, PageFormat pf, int page)
		{
		
		Scanner scanner = new Scanner(finger_string);
		String s;

		if (page > 0) return NO_SUCH_PAGE;
		Graphics2D g2d =  (Graphics2D)g;
		g2d.setFont(new Font("CourierThai", Font.PLAIN, 10));
		g2d.translate(pf.getImageableX(), pf.getImageableY());
	
		int x = (int) pf.getImageableX();
		int y = (int) pf.getImageableY();

		while(scanner.hasNextLine()) {
		        s = scanner.nextLine(); 
			y+= 12;
			g2d.drawString(s, x, y);
		}
		scanner.close();
		
		 // g.drawString(finger_string, 20, 20);
		return PAGE_EXISTS;
	}

	public void actionPerformed(ActionEvent e)
	{
		if(e.getSource() == button)
		{
		site = textfield.getText();
//		System.out.println(site);
		textfield.setText("");
		textarea = new JTextArea("");

		success = networking();
		if(success == 0) 
			{
			// frame.setSize(600, 800);
			printing_on_screen();
			// frame.setSize(600, 200);
			}
		}

		if(e.getSource() == printbutton)
		{
			printing_on_paper();
		}
	}

	public static void main(String args[])
	{
		new textfinger();
	}
}
