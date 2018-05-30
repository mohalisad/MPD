using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MPD
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }


        private void button1_Click(object sender, EventArgs e)
        {
            //textBox3.Text= new Cryptor().decrypt(textBox2.Text, textBox1.Text);
            //textBox3.Text = new Cryptor().decrypt(new Cryptor().decrypt(textBox2.Text, textBox1.Text).Split(' ')[2], "entry_key1234");
            textBox3.Text = new Cryptor().encrypt(textBox2.Text, textBox1.Text);
        }

        private void button2_Click(object sender, EventArgs e) {
            string t = textBox2.Text;
            textBox2.Text = textBox3.Text;
            textBox3.Text = t;
        }

        private void button3_Click(object sender, EventArgs e) {
            textBox3.Text = new Cryptor().decrypt(textBox2.Text, textBox1.Text);
            //textBox3.Text = Encoding.UTF8.GetString( Encoding.UTF8.GetBytes(textBox2.Text));
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            textBox1.Text = Date.now();
        }
    }
}
