#pragma once
#include "windows.h"
namespace labaaftergraphics {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			pb_for_clock->Image = gcnew Bitmap(pb_for_clock->Width, pb_for_clock->Height);
			b = gcnew SolidBrush(Color::White);
			pn_contour = gcnew Pen(Color::Black, 3);
			pn_arrows = gcnew Pen(Color::Green, 3);
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btn_clock;
	private: System::Windows::Forms::PictureBox^ pb_for_clock;
	protected:


	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btn_clock = (gcnew System::Windows::Forms::Button());
			this->pb_for_clock = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_for_clock))->BeginInit();
			this->SuspendLayout();
			// 
			// btn_clock
			// 
			this->btn_clock->Location = System::Drawing::Point(518, 65);
			this->btn_clock->Name = L"btn_clock";
			this->btn_clock->Size = System::Drawing::Size(114, 38);
			this->btn_clock->TabIndex = 0;
			this->btn_clock->Text = L"Построить";
			this->btn_clock->UseVisualStyleBackColor = true;
			this->btn_clock->Click += gcnew System::EventHandler(this, &MyForm::btn_clock_Click);
			// 
			// pb_for_clock
			// 
			this->pb_for_clock->Location = System::Drawing::Point(12, 12);
			this->pb_for_clock->Name = L"pb_for_clock";
			this->pb_for_clock->Size = System::Drawing::Size(500, 500);
			this->pb_for_clock->TabIndex = 1;
			this->pb_for_clock->TabStop = false;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(652, 527);
			this->Controls->Add(this->pb_for_clock);
			this->Controls->Add(this->btn_clock);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_for_clock))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
		Brush^ b;
		Pen^ pn_contour, ^ pn_arrows;
		bool kk = true;

		void clear(Image^ img, Brush^ b) {
			Graphics^ gr = Graphics::FromImage(img);
			gr->FillRectangle(b, 0, 0, img->Width, img->Height);
		}
		PointF rotate(PointF p, PointF c, float phi) {
			return PointF(c.X + (p.X - c.X) * Math::Cos(phi) - (p.Y - c.Y) * Math::Sin(phi),
				c.Y + (p.X - c.X) * Math::Sin(phi) + (p.Y - c.Y) * Math::Cos(phi));
		}
		void drawclock(Image^ img, Brush^ b,
			Pen^ pn_contour, Pen^ pn_arrows,
			PointF center, float r, float dash_len,
			float h_len, float m_len, float s_len, DateTime time) {

			Graphics^ gr = Graphics::FromImage(img);
			gr->FillEllipse(b, center.X - r, center.Y - r, 2 * r, 2 * r);
			gr->DrawEllipse(pn_contour, center.X - r, center.Y - r, 2 * r, 2 * r);

			int n = 12;
			float phi = 0,
				dphi = 2 * Math::PI / n;
			Point po(center.X, center.Y - r),
				p1(po.X, po.Y + dash_len);

			for (int i = 0; i < n; i++) {
				PointF ps = rotate(po, center, phi + i * dphi);
				PointF pe = rotate(p1, center, phi + i * dphi);
				gr->DrawLine(pn_contour, ps, pe);
			}

			float s = 2 * Math::PI / 60 * time.Second,
				m = 2 * Math::PI / 60 * time.Minute + s / 60,
				h = 2 * Math::PI / 12 * time.Hour + m / 12;
			PointF hend = rotate(PointF(center.X, center.Y - h_len), center, h),
				mend = rotate(PointF(center.X, center.Y - m_len), center, m),
				send = rotate(PointF(center.X, center.Y - s_len), center, s);
			gr->DrawLine(pn_arrows, center, hend);
			gr->DrawLine(pn_arrows, center, mend);
			gr->DrawLine(pn_arrows, center, send);
		}
	private: System::Void btn_clock_Click(System::Object^ sender, System::EventArgs^ e) {
		Point p(150, 150);
		float r = 125, dash_len = 20, h_len = 50, m_len = 80, s_len = 120;
		while (kk) {
			clear(pb_for_clock->Image, b);
			System::DateTime time = DateTime::Now;
			drawclock(pb_for_clock->Image, b, pn_contour, pn_arrows, p, r, dash_len, h_len, m_len, s_len, time);
			pb_for_clock->Refresh();
			Sleep(1000);
		}
	}
	};
}/*реализовать функцию, которая считывает точки, указанные пользоваетелем и записывает в listbox
 повернуть на угол(данные для угла) относительно начала координат, относительно вершины
 сдвинуть на расстояние(данные расстояния) по горизонтали, по вертикали
 менять масштаб относительно точки многоугольника или относительно начала координат
 */
