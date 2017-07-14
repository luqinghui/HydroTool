namespace UserForm
{
    partial class MainForm
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.depressionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.fillDepressionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.identifyDepressionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.flowDirectionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.d8ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pFToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pFJiangToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.flowAccumulationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.originalToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.depressionToolStripMenuItem,
            this.flowDirectionToolStripMenuItem,
            this.flowAccumulationToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(690, 25);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // depressionToolStripMenuItem
            // 
            this.depressionToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fillDepressionToolStripMenuItem,
            this.identifyDepressionToolStripMenuItem});
            this.depressionToolStripMenuItem.Name = "depressionToolStripMenuItem";
            this.depressionToolStripMenuItem.Size = new System.Drawing.Size(86, 21);
            this.depressionToolStripMenuItem.Text = "Depression";
            // 
            // fillDepressionToolStripMenuItem
            // 
            this.fillDepressionToolStripMenuItem.Name = "fillDepressionToolStripMenuItem";
            this.fillDepressionToolStripMenuItem.Size = new System.Drawing.Size(185, 22);
            this.fillDepressionToolStripMenuItem.Text = "FillDepression";
            this.fillDepressionToolStripMenuItem.Click += new System.EventHandler(this.fillDepressionToolStripMenuItem_Click);
            // 
            // identifyDepressionToolStripMenuItem
            // 
            this.identifyDepressionToolStripMenuItem.Name = "identifyDepressionToolStripMenuItem";
            this.identifyDepressionToolStripMenuItem.Size = new System.Drawing.Size(185, 22);
            this.identifyDepressionToolStripMenuItem.Text = "IdentifyDepression";
            this.identifyDepressionToolStripMenuItem.Click += new System.EventHandler(this.identifyDepressionToolStripMenuItem_Click);
            // 
            // flowDirectionToolStripMenuItem
            // 
            this.flowDirectionToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.d8ToolStripMenuItem,
            this.pFToolStripMenuItem,
            this.pFJiangToolStripMenuItem});
            this.flowDirectionToolStripMenuItem.Name = "flowDirectionToolStripMenuItem";
            this.flowDirectionToolStripMenuItem.Size = new System.Drawing.Size(102, 21);
            this.flowDirectionToolStripMenuItem.Text = "Flow Direction";
            // 
            // d8ToolStripMenuItem
            // 
            this.d8ToolStripMenuItem.Name = "d8ToolStripMenuItem";
            this.d8ToolStripMenuItem.Size = new System.Drawing.Size(127, 22);
            this.d8ToolStripMenuItem.Text = "D8";
            this.d8ToolStripMenuItem.Click += new System.EventHandler(this.d8ToolStripMenuItem_Click);
            // 
            // pFToolStripMenuItem
            // 
            this.pFToolStripMenuItem.Name = "pFToolStripMenuItem";
            this.pFToolStripMenuItem.Size = new System.Drawing.Size(127, 22);
            this.pFToolStripMenuItem.Text = "PF";
            this.pFToolStripMenuItem.Click += new System.EventHandler(this.pFToolStripMenuItem_Click);
            // 
            // pFJiangToolStripMenuItem
            // 
            this.pFJiangToolStripMenuItem.Name = "pFJiangToolStripMenuItem";
            this.pFJiangToolStripMenuItem.Size = new System.Drawing.Size(127, 22);
            this.pFJiangToolStripMenuItem.Text = "PF(Jiang)";
            // 
            // flowAccumulationToolStripMenuItem
            // 
            this.flowAccumulationToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.originalToolStripMenuItem});
            this.flowAccumulationToolStripMenuItem.Name = "flowAccumulationToolStripMenuItem";
            this.flowAccumulationToolStripMenuItem.Size = new System.Drawing.Size(127, 21);
            this.flowAccumulationToolStripMenuItem.Text = "Flow Accumulation";
            // 
            // originalToolStripMenuItem
            // 
            this.originalToolStripMenuItem.Name = "originalToolStripMenuItem";
            this.originalToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.originalToolStripMenuItem.Text = "Original";
            this.originalToolStripMenuItem.Click += new System.EventHandler(this.originalToolStripMenuItem_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(690, 49);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MainForm";
            this.Text = "Form1";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem depressionToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem fillDepressionToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem identifyDepressionToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem flowDirectionToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem d8ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem pFToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem pFJiangToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem flowAccumulationToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem originalToolStripMenuItem;
    }
}

