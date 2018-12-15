#pragma once
#include <iostream>
#include <msclr\marshal_cppstd.h>

#include "NonLocalMeans.h"
#include "Bilateral.h"


using namespace cv;

namespace NoiseRemoving {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ NoiseRemoving
	/// </summary>
	public ref class NoiseRemoving : public System::Windows::Forms::Form
	{
	public:

		NoiseRemoving(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	private: System::Windows::Forms::PictureBox^  modifiedNonLocalPicture;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;

	public:
			 System::String^ picturePath;

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~NoiseRemoving()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  originalPicture;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::PictureBox^  modifiedBilateralPicture;







	protected:

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->originalPicture = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->modifiedBilateralPicture = (gcnew System::Windows::Forms::PictureBox());
			this->modifiedNonLocalPicture = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->originalPicture))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->modifiedBilateralPicture))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->modifiedNonLocalPicture))->BeginInit();
			this->SuspendLayout();
			// 
			// originalPicture
			// 
			this->originalPicture->Location = System::Drawing::Point(22, 104);
			this->originalPicture->Name = L"originalPicture";
			this->originalPicture->Size = System::Drawing::Size(419, 266);
			this->originalPicture->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->originalPicture->TabIndex = 0;
			this->originalPicture->TabStop = false;
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->button1->Location = System::Drawing::Point(22, 32);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(223, 40);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Open picture";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &NoiseRemoving::button1_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// modifiedBilateralPicture
			// 
			this->modifiedBilateralPicture->Location = System::Drawing::Point(460, 104);
			this->modifiedBilateralPicture->Name = L"modifiedBilateralPicture";
			this->modifiedBilateralPicture->Size = System::Drawing::Size(419, 266);
			this->modifiedBilateralPicture->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->modifiedBilateralPicture->TabIndex = 2;
			this->modifiedBilateralPicture->TabStop = false;
			// 
			// modifiedNonLocalPicture
			// 
			this->modifiedNonLocalPicture->Location = System::Drawing::Point(899, 104);
			this->modifiedNonLocalPicture->Name = L"modifiedNonLocalPicture";
			this->modifiedNonLocalPicture->Size = System::Drawing::Size(419, 266);
			this->modifiedNonLocalPicture->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->modifiedNonLocalPicture->TabIndex = 6;
			this->modifiedNonLocalPicture->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(15, 383);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(240, 38);
			this->label1->TabIndex = 7;
			this->label1->Text = L"Original Picture";
			this->label1->Visible = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(453, 383);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(215, 38);
			this->label2->TabIndex = 8;
			this->label2->Text = L"Bilateral Filter";
			this->label2->Visible = false;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(892, 383);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(262, 38);
			this->label3->TabIndex = 9;
			this->label3->Text = L"Non-local Means";
			this->label3->Visible = false;
			// 
			// NoiseRemoving
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1337, 473);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->modifiedNonLocalPicture);
			this->Controls->Add(this->modifiedBilateralPicture);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->originalPicture);
			this->Name = L"NoiseRemoving";
			this->Text = L"NoiseRemoving";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->originalPicture))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->modifiedBilateralPicture))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->modifiedNonLocalPicture))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			Mat image;
			picturePath = openFileDialog1->FileName;
			System::String^ path = openFileDialog1->FileName;
			originalPicture->ImageLocation = picturePath;
			std::string strPicturePath = msclr::interop::marshal_as<std::string>(path);

			image = imread(strPicturePath, 1);
			if (!image.data)
			{
				MessageBox::Show("No image data", "Warning");
				label1->Visible = false;
				label2->Visible = false;
				label3->Visible = false;
				return;
			}

			label1->Visible = true;
			label2->Visible = true;
			label3->Visible = true;

			Mat filteredImageOpenCVNL;
			nonlocalMeansFilter(image, filteredImageOpenCVNL, 3, 7, 15.0, 15.0);
			imwrite("filtered_image_NL.png", filteredImageOpenCVNL);

			modifiedNonLocalPicture->ImageLocation = "filtered_image_NL.png";

			image = imread(strPicturePath, 0);
			Mat filteredImageOpenCV;
			bilateralFilter(image, filteredImageOpenCV, 7, 35.0, 5.0);
			imwrite("filtered_image_OpenCV.png", filteredImageOpenCV);
			Mat filteredImageOwn = bilateralFilterOwn(image, 7, 35.0, 5.0);
			imwrite("filtered_image_own.png", filteredImageOwn);

			modifiedBilateralPicture->ImageLocation = "filtered_image_own.png";

		}
	}
	private: System::Void radioButton1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	}
private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {

}

};
}