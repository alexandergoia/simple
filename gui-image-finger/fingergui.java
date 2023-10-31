/*
 *
 *	GUI Finger for Windows/Java
 *
 */

import java.io.*;
import java.net.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.print.*;
import java.awt.image.*;
import javax.swing.*;
import javax.imageio.*;

class fingergui implements ActionListener, KeyListener, Printable
{
	JFrame     frame;
	JButton    button;
	JTextField textfield;

	File 	      file;
	BufferedImage bufferedImage;
        Image         image;
	ImageIcon     icon;

	JPanel	   panel;
	JLabel	   label;

	fingergui () 
	{
		frame = new JFrame("Simple Touch");
		frame.setSize(600, 200);

		textfield = new JTextField();
		textfield.setBounds(100, 50, 250, 30);

		button = new JButton("Touch !");
		button.setBounds(450, 50, 100, 30);

		button.addActionListener(this);
		
		textfield.addKeyListener(this);

		frame.add(textfield);
		frame.add(button);

		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setResizable(false);
		frame.setLayout(null);
		frame.setVisible(true);
	}

	public static void main(String args[])
	{
		new fingergui();
	}

	public void keyPressed(KeyEvent e)
	{
		if(e.getKeyCode() == KeyEvent.VK_ENTER)
		{
			String text = textfield.getText();
			textfield.setText("");
		
			try {	
			InetAddress inetaddr = InetAddress.getByName(text);
			Socket socket = new Socket(inetaddr, 9700);
	
			file = new File("image.jpg");
			file.createNewFile();

			FileOutputStream fis = new FileOutputStream(file);

			byte[] buffer = new byte[4096];
			BufferedInputStream is = new BufferedInputStream
				(socket.getInputStream());
			int read;

			while((read = is.read(buffer)) != -1)
				fis.write(buffer, 0, read);
			}
			catch(IOException ioe) {}

			printimage(file);

		}


	}

	public void keyReleased(KeyEvent e)
	{
	}

	public void keyTyped(KeyEvent e)
	{
	}

	public void actionPerformed(ActionEvent e)
	{
		if(e.getSource() == button)
		{
			String text = textfield.getText();
			textfield.setText("");
		
			try {	
			InetAddress inetaddr = InetAddress.getByName(text);
			Socket socket = new Socket(inetaddr, 9700);
	
			file = new File("image.jpg");
			file.createNewFile();

			FileOutputStream fis = new FileOutputStream(file);

			byte[] buffer = new byte[4096];
			BufferedInputStream is = new BufferedInputStream
				(socket.getInputStream());
			int read;

			while((read = is.read(buffer)) != -1)
				fis.write(buffer, 0, read);
			}
			catch(IOException ioe) {}

			printimage(file);

		}
	}

	public void printimage(File file)
	{
		try {
		bufferedImage = ImageIO.read(file);
		image = bufferedImage.getScaledInstance(400, 400, Image.SCALE_DEFAULT);
		icon = new ImageIcon(image);
		} catch(IOException ioe) {}

		label = new JLabel();
		label.setIcon(icon);

		panel = new JPanel();
		panel.setBounds(0, 150, 600, 600);

		panel.add(label);
		frame.add(panel);
		
	       	frame.setSize(600, 600);
		frame.setLayout(null);
		frame.setVisible(true);
		
		// PrinterJob job = PrinterJob.getPrinterJob();
		// job.setPrintable(this);
		// try { job.print(); }
		// catch(PrinterException e) {}
	}

	public int print(Graphics g, PageFormat pf, int page)
		throws PrinterException
	{
		if (page > 0) return NO_SUCH_PAGE;

		Graphics2D g2d = (Graphics2D) g;
		g2d.translate(pf.getImageableX(), pf.getImageableY());

		g.drawImage(image, 0, 0, null);

		return PAGE_EXISTS;
	}
}
