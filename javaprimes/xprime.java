import java.lang.*;
import java.math.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class xprime implements ActionListener {

	JFrame frame;
	JTextField field;
	JButton button;
	int nr;

	mathprime m;

	JFrame frame2;
	JLabel label2;
	JButton button2;

	xprime() {
		
		frame = new JFrame("Test primes");
		frame.setSize(300, 150);
		frame.setLayout(new FlowLayout());
		field = new JTextField(20);
		frame.add(field);
		button = new JButton("Test!");
		button.setBounds(50, 50, 25, 25);
		frame.add(button);
		button.addActionListener(this);
		frame.setLocationRelativeTo(null);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);

	}


	public void actionPerformed(ActionEvent e) {
		
		if(field.getText().equals("")) return;

		nr = Integer.valueOf(field.getText());
		m = new mathprime(nr);

		frame2 = new JFrame("Result");
		frame2.setSize(300, 150);
		frame2.setLayout(new FlowLayout());
		if(m.is_prime() == 1)
			label2 = new JLabel(nr + " is not prime");
		else
			label2 = new JLabel(nr + " is prime");
		frame2.add(label2);
		button2 = new JButton("ok");
		frame2.add(button2);
		button2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				frame2.dispose();
				field.setText("");
			}
		});
		frame2.setLocationRelativeTo(null);
		frame2.setVisible(true);


	}

	public static void main(String args[]) {

		new xprime();

	}
}


class mathprime {

	int x;

	mathprime(int no) {
	       x = no;
	}

	int is_prime() {

		int i;

		if(x == 1) return 1;
		if(x == 2 || x == 3) return 0;
		if(x == 4) return 1;

		for(i = 2; i <= (int) Math.sqrt(x); i = i + 2)
			if(x % i == 0)
				return 1;

		return 0;
	}		
}
