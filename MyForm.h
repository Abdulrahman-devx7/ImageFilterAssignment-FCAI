#pragma once
#include "Image_Class.h"
#include "Filters.h"
#include "ImageHistory.h"
#include <msclr/marshal_cppstd.h>

namespace BabyPhotoshop {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Drawing::Imaging;
    using namespace System::Runtime::InteropServices;

    // Helper class to show input dialog boxes
    public ref class Prompt
    {
    public:
        static String^ ShowDialog(String^ text, String^ caption)
        {
            Form^ prompt = gcnew Form();
            prompt->Width = 320;
            prompt->Height = 160;
            prompt->FormBorderStyle = FormBorderStyle::FixedDialog;
            prompt->Text = caption;
            prompt->StartPosition = FormStartPosition::CenterScreen;
            prompt->MaximizeBox = false;
            prompt->MinimizeBox = false;

            Label^ textLabel = gcnew Label();
            textLabel->Left = 20;
            textLabel->Top = 20;
            textLabel->Width = 260;
            textLabel->Text = text;

            TextBox^ textBox = gcnew TextBox();
            textBox->Left = 20;
            textBox->Top = 50;
            textBox->Width = 260;

            Button^ confirmation = gcnew Button();
            confirmation->Text = L"OK";
            confirmation->Left = 180;
            confirmation->Top = 85;
            confirmation->Width = 100;
            confirmation->DialogResult = System::Windows::Forms::DialogResult::OK;

            prompt->Controls->Add(textLabel);
            prompt->Controls->Add(textBox);
            prompt->Controls->Add(confirmation);
            prompt->AcceptButton = confirmation;

            return prompt->ShowDialog() == System::Windows::Forms::DialogResult::OK ? textBox->Text : L"";
        }

        // Helper that shows a choice dialog (e.g., flip direction, blur level)
        static int ShowChoice(String^ text, String^ caption, cli::array<String^>^ options)
        {
            Form^ prompt = gcnew Form();
            prompt->Width = 320;
            prompt->Height = 60 + options->Length * 40 + 20;
            prompt->FormBorderStyle = FormBorderStyle::FixedDialog;
            prompt->Text = caption;
            prompt->StartPosition = FormStartPosition::CenterScreen;
            prompt->MaximizeBox = false;
            prompt->MinimizeBox = false;

            Label^ textLabel = gcnew Label();
            textLabel->Left = 20;
            textLabel->Top = 10;
            textLabel->Width = 260;
            textLabel->Text = text;
            prompt->Controls->Add(textLabel);

            for (int i = 0; i < options->Length; i++) {
                Button^ btn = gcnew Button();
                btn->Text = options[i];
                btn->Left = 20;
                btn->Top = 40 + i * 40;
                btn->Width = 260;
                btn->Height = 35;
                btn->Tag = i;
                btn->DialogResult = System::Windows::Forms::DialogResult::OK;
                prompt->Controls->Add(btn);
            }

            prompt->ShowDialog();
            return -1;
        }
    };

    public ref class DarkStatusStripRenderer : public System::Windows::Forms::ToolStripProfessionalRenderer
    {
    protected:
        virtual void OnRenderToolStripBackground(System::Windows::Forms::ToolStripRenderEventArgs^ e) override
        {
            System::Drawing::SolidBrush^ brush = gcnew System::Drawing::SolidBrush(e->ToolStrip->BackColor);
            e->Graphics->FillRectangle(brush, e->AffectedBounds);
            delete brush;
        }

        virtual void OnRenderToolStripBorder(System::Windows::Forms::ToolStripRenderEventArgs^ e) override
        {
            System::Drawing::Pen^ pen = gcnew System::Drawing::Pen(System::Drawing::Color::FromArgb(45, 45, 52), 1.0f);
            e->Graphics->DrawLine(pen, 0, 0, e->ToolStrip->Width, 0);
            delete pen;
        }
    };

    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
            currentImage = new ::Image();
            history = nullptr;
            cropInteractionMode = false;
            isSelectingCrop = false;
            cropStartX = 0;
            cropStartY = 0;
            cropCurrentX = 0;
            cropCurrentY = 0;
            UpdateHistoryButtons();
            UpdateStatusTelemetry(L"Ready - Load or drop an image to begin");
        }

    protected:
        ~MyForm()
        {
            if (components) delete components;
            if (currentImage) delete currentImage;
            if (history) {
                delete history;
                history = nullptr;
            }
        }

    private:
        ::Image* currentImage;
        ImageHistory* history;

        // Interactive Crop tracking
        bool cropInteractionMode;
        bool isSelectingCrop;
        int cropStartX;
        int cropStartY;
        int cropCurrentX;
        int cropCurrentY;

        // UI Elements
        System::Windows::Forms::PictureBox^ pictureBox1;
        System::Windows::Forms::Button^ btnLoad;
        System::Windows::Forms::Button^ btnSave;
        System::Windows::Forms::Button^ btnBackward;
        System::Windows::Forms::Button^ btnForward;
        System::Windows::Forms::FlowLayoutPanel^ filterPanel;
        System::Windows::Forms::Panel^ mainPanel;

        // Status Bar & Telemetry Controls
        System::Windows::Forms::StatusStrip^ statusStrip1;
        System::Windows::Forms::ToolStripStatusLabel^ statusLabelMsg;
        System::Windows::Forms::ToolStripStatusLabel^ statusLabelDim;
        System::Windows::Forms::ToolStripStatusLabel^ statusLabelChannels;
        System::Windows::Forms::ToolStripStatusLabel^ statusLabelHistory;

        // All 18 filter buttons
        System::Windows::Forms::Button^ btn1;
        System::Windows::Forms::Button^ btn2;
        System::Windows::Forms::Button^ btn3;
        System::Windows::Forms::Button^ btn4;
        System::Windows::Forms::Button^ btn5;
        System::Windows::Forms::Button^ btn6;
        System::Windows::Forms::Button^ btn7;
        System::Windows::Forms::Button^ btn8;
        System::Windows::Forms::Button^ btn9;
        System::Windows::Forms::Button^ btn10;
        System::Windows::Forms::Button^ btn11;
        System::Windows::Forms::Button^ btn12;
        System::Windows::Forms::Button^ btn13;
        System::Windows::Forms::Button^ btn14;
        System::Windows::Forms::Button^ btn15;
        System::Windows::Forms::Button^ btn16;
        System::Windows::Forms::Button^ btn17;
        System::Windows::Forms::Button^ btn18;

        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
            this->btnLoad = (gcnew System::Windows::Forms::Button());
            this->btnSave = (gcnew System::Windows::Forms::Button());
            this->btnBackward = (gcnew System::Windows::Forms::Button());
            this->btnForward = (gcnew System::Windows::Forms::Button());
            this->filterPanel = (gcnew System::Windows::Forms::FlowLayoutPanel());
            this->mainPanel = (gcnew System::Windows::Forms::Panel());

            this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
            this->statusLabelMsg = (gcnew System::Windows::Forms::ToolStripStatusLabel());
            this->statusLabelDim = (gcnew System::Windows::Forms::ToolStripStatusLabel());
            this->statusLabelChannels = (gcnew System::Windows::Forms::ToolStripStatusLabel());
            this->statusLabelHistory = (gcnew System::Windows::Forms::ToolStripStatusLabel());

            this->btn1 = (gcnew System::Windows::Forms::Button());
            this->btn2 = (gcnew System::Windows::Forms::Button());
            this->btn3 = (gcnew System::Windows::Forms::Button());
            this->btn4 = (gcnew System::Windows::Forms::Button());
            this->btn5 = (gcnew System::Windows::Forms::Button());
            this->btn6 = (gcnew System::Windows::Forms::Button());
            this->btn7 = (gcnew System::Windows::Forms::Button());
            this->btn8 = (gcnew System::Windows::Forms::Button());
            this->btn9 = (gcnew System::Windows::Forms::Button());
            this->btn10 = (gcnew System::Windows::Forms::Button());
            this->btn11 = (gcnew System::Windows::Forms::Button());
            this->btn12 = (gcnew System::Windows::Forms::Button());
            this->btn13 = (gcnew System::Windows::Forms::Button());
            this->btn14 = (gcnew System::Windows::Forms::Button());
            this->btn15 = (gcnew System::Windows::Forms::Button());
            this->btn16 = (gcnew System::Windows::Forms::Button());
            this->btn17 = (gcnew System::Windows::Forms::Button());
            this->btn18 = (gcnew System::Windows::Forms::Button());

            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
            this->filterPanel->SuspendLayout();
            this->statusStrip1->SuspendLayout();
            this->SuspendLayout();

            //
            // pictureBox1
            //
            this->pictureBox1->BackColor = System::Drawing::Color::FromArgb(34, 34, 38);
            this->pictureBox1->Location = System::Drawing::Point(270, 10);
            this->pictureBox1->Name = L"pictureBox1";
            this->pictureBox1->Size = System::Drawing::Size(740, 535);
            this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
            this->pictureBox1->TabIndex = 0;
            this->pictureBox1->TabStop = false;
            this->pictureBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right);
            this->pictureBox1->AllowDrop = true;
            this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseDown);
            this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseMove);
            this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseUp);
            this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pictureBox1_Paint);
            this->pictureBox1->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &MyForm::pictureBox1_DragEnter);
            this->pictureBox1->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &MyForm::pictureBox1_DragDrop);
            //
            // btnLoad
            //
            this->btnLoad->BackColor = System::Drawing::Color::FromArgb(0, 122, 204);
            this->btnLoad->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnLoad->FlatAppearance->BorderSize = 0;
            this->btnLoad->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(28, 151, 234);
            this->btnLoad->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(0, 102, 174);
            this->btnLoad->Cursor = System::Windows::Forms::Cursors::Hand;
            this->btnLoad->ForeColor = System::Drawing::Color::White;
            this->btnLoad->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
            this->btnLoad->Location = System::Drawing::Point(280, 555);
            this->btnLoad->Name = L"btnLoad";
            this->btnLoad->Size = System::Drawing::Size(120, 40);
            this->btnLoad->TabIndex = 1;
            this->btnLoad->Text = L"Load Image";
            this->btnLoad->UseVisualStyleBackColor = false;
            this->btnLoad->Click += gcnew System::EventHandler(this, &MyForm::btnLoad_Click);
            this->btnLoad->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left);
            //
            // btnSave
            //
            this->btnSave->BackColor = System::Drawing::Color::FromArgb(30, 130, 76);
            this->btnSave->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnSave->FlatAppearance->BorderSize = 0;
            this->btnSave->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(40, 167, 98);
            this->btnSave->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(24, 106, 62);
            this->btnSave->Cursor = System::Windows::Forms::Cursors::Hand;
            this->btnSave->ForeColor = System::Drawing::Color::White;
            this->btnSave->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
            this->btnSave->Location = System::Drawing::Point(415, 555);
            this->btnSave->Name = L"btnSave";
            this->btnSave->Size = System::Drawing::Size(120, 40);
            this->btnSave->TabIndex = 2;
            this->btnSave->Text = L"Save Image";
            this->btnSave->UseVisualStyleBackColor = false;
            this->btnSave->Click += gcnew System::EventHandler(this, &MyForm::btnSave_Click);
            this->btnSave->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left);
            //
            // btnBackward
            //
            this->btnBackward->BackColor = System::Drawing::Color::FromArgb(45, 45, 48);
            this->btnBackward->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnBackward->FlatAppearance->BorderSize = 0;
            this->btnBackward->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(115, 85, 175);
            this->btnBackward->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(75, 50, 120);
            this->btnBackward->ForeColor = System::Drawing::Color::FromArgb(100, 100, 100);
            this->btnBackward->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
            this->btnBackward->Location = System::Drawing::Point(550, 555);
            this->btnBackward->Name = L"btnBackward";
            this->btnBackward->Size = System::Drawing::Size(140, 40);
            this->btnBackward->TabIndex = 4;
            this->btnBackward->Text = L"<- Backward";
            this->btnBackward->UseVisualStyleBackColor = false;
            this->btnBackward->Enabled = false;
            this->btnBackward->Click += gcnew System::EventHandler(this, &MyForm::btnBackward_Click);
            this->btnBackward->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left);
            //
            // btnForward
            //
            this->btnForward->BackColor = System::Drawing::Color::FromArgb(45, 45, 48);
            this->btnForward->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnForward->FlatAppearance->BorderSize = 0;
            this->btnForward->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(115, 85, 175);
            this->btnForward->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(75, 50, 120);
            this->btnForward->ForeColor = System::Drawing::Color::FromArgb(100, 100, 100);
            this->btnForward->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
            this->btnForward->Location = System::Drawing::Point(705, 555);
            this->btnForward->Name = L"btnForward";
            this->btnForward->Size = System::Drawing::Size(140, 40);
            this->btnForward->TabIndex = 5;
            this->btnForward->Text = L"Forward ->";
            this->btnForward->UseVisualStyleBackColor = false;
            this->btnForward->Enabled = false;
            this->btnForward->Click += gcnew System::EventHandler(this, &MyForm::btnForward_Click);
            this->btnForward->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left);
            //
            // filterPanel
            //
            this->filterPanel->AutoScroll = true;
            this->filterPanel->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
            this->filterPanel->WrapContents = false;
            this->filterPanel->Location = System::Drawing::Point(5, 10);
            this->filterPanel->Name = L"filterPanel";
            this->filterPanel->Size = System::Drawing::Size(255, 595);
            this->filterPanel->TabIndex = 3;
            this->filterPanel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left);
            //
            // statusStrip1
            //
            this->statusStrip1->BackColor = System::Drawing::Color::FromArgb(22, 22, 26);
            this->statusStrip1->ForeColor = System::Drawing::Color::FromArgb(190, 190, 198);
            this->statusStrip1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.0f));
            this->statusStrip1->SizingGrip = false;
            this->statusStrip1->Renderer = gcnew DarkStatusStripRenderer();
            this->statusStrip1->Items->AddRange(gcnew cli::array<System::Windows::Forms::ToolStripItem^> {
                this->statusLabelMsg,
                this->statusLabelDim,
                this->statusLabelChannels,
                this->statusLabelHistory
            });
            this->statusStrip1->Location = System::Drawing::Point(0, 614);
            this->statusStrip1->Name = L"statusStrip1";
            this->statusStrip1->Size = System::Drawing::Size(1020, 26);
            this->statusStrip1->TabIndex = 6;
            this->statusStrip1->Text = L"statusStrip1";
            //
            // statusLabelMsg
            //
            this->statusLabelMsg->Name = L"statusLabelMsg";
            this->statusLabelMsg->Spring = true;
            this->statusLabelMsg->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            this->statusLabelMsg->Text = L"Ready - Load or drop an image to begin";
            this->statusLabelMsg->ForeColor = System::Drawing::Color::FromArgb(220, 220, 228);
            //
            // statusLabelDim
            //
            this->statusLabelDim->Name = L"statusLabelDim";
            this->statusLabelDim->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>(System::Windows::Forms::ToolStripStatusLabelBorderSides::Left);
            this->statusLabelDim->BorderStyle = System::Windows::Forms::Border3DStyle::Etched;
            this->statusLabelDim->Padding = System::Windows::Forms::Padding(8, 0, 8, 0);
            this->statusLabelDim->Text = L"-- x -- px";
            this->statusLabelDim->ForeColor = System::Drawing::Color::FromArgb(0, 185, 255);
            //
            // statusLabelChannels
            //
            this->statusLabelChannels->Name = L"statusLabelChannels";
            this->statusLabelChannels->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>(System::Windows::Forms::ToolStripStatusLabelBorderSides::Left);
            this->statusLabelChannels->BorderStyle = System::Windows::Forms::Border3DStyle::Etched;
            this->statusLabelChannels->Padding = System::Windows::Forms::Padding(8, 0, 8, 0);
            this->statusLabelChannels->Text = L"-- Channels";
            this->statusLabelChannels->ForeColor = System::Drawing::Color::FromArgb(160, 215, 130);
            //
            // statusLabelHistory
            //
            this->statusLabelHistory->Name = L"statusLabelHistory";
            this->statusLabelHistory->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>(System::Windows::Forms::ToolStripStatusLabelBorderSides::Left);
            this->statusLabelHistory->BorderStyle = System::Windows::Forms::Border3DStyle::Etched;
            this->statusLabelHistory->Padding = System::Windows::Forms::Padding(8, 0, 8, 0);
            this->statusLabelHistory->Text = L"History: Idle";
            this->statusLabelHistory->ForeColor = System::Drawing::Color::FromArgb(210, 175, 255);

            // Create all 18 buttons with names
            cli::array<String^>^ names = gcnew cli::array<String^> {
                L"1. Grayscale", L"2. Black & White", L"3. Invert",
                L"4. Add Frame", L"5. Flip", L"6. Rotate",
                L"7. Darken/Lighten", L"8. Resize", L"9. Merge",
                L"10. Edge Detect", L"11. Crop", L"12. Blur",
                L"13. Sunlight", L"14. TV Effect", L"15. Purple",
                L"16. Infrared", L"17. Skew", L"18. Oil Paint"
            };

            cli::array<Button^>^ btns = gcnew cli::array<Button^> {
                btn1, btn2, btn3, btn4, btn5, btn6,
                btn7, btn8, btn9, btn10, btn11, btn12,
                btn13, btn14, btn15, btn16, btn17, btn18
            };

            cli::array<System::EventHandler^>^ handlers = gcnew cli::array<System::EventHandler^> {
                gcnew System::EventHandler(this, &MyForm::btn1_Click),
                gcnew System::EventHandler(this, &MyForm::btn2_Click),
                gcnew System::EventHandler(this, &MyForm::btn3_Click),
                gcnew System::EventHandler(this, &MyForm::btn4_Click),
                gcnew System::EventHandler(this, &MyForm::btn5_Click),
                gcnew System::EventHandler(this, &MyForm::btn6_Click),
                gcnew System::EventHandler(this, &MyForm::btn7_Click),
                gcnew System::EventHandler(this, &MyForm::btn8_Click),
                gcnew System::EventHandler(this, &MyForm::btn9_Click),
                gcnew System::EventHandler(this, &MyForm::btn10_Click),
                gcnew System::EventHandler(this, &MyForm::btn11_Click),
                gcnew System::EventHandler(this, &MyForm::btn12_Click),
                gcnew System::EventHandler(this, &MyForm::btn13_Click),
                gcnew System::EventHandler(this, &MyForm::btn14_Click),
                gcnew System::EventHandler(this, &MyForm::btn15_Click),
                gcnew System::EventHandler(this, &MyForm::btn16_Click),
                gcnew System::EventHandler(this, &MyForm::btn17_Click),
                gcnew System::EventHandler(this, &MyForm::btn18_Click)
            };

            for (int i = 0; i < 18; i++) {
                btns[i]->Size = System::Drawing::Size(232, 42);
                btns[i]->Text = names[i];
                btns[i]->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
                btns[i]->FlatAppearance->BorderSize = 0;
                btns[i]->BackColor = System::Drawing::Color::FromArgb(46, 46, 52);
                btns[i]->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(65, 65, 74);
                btns[i]->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(0, 122, 204);
                btns[i]->ForeColor = System::Drawing::Color::White;
                btns[i]->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10.0f, System::Drawing::FontStyle::Bold));
                btns[i]->TextAlign = ContentAlignment::MiddleLeft;
                btns[i]->Padding = System::Windows::Forms::Padding(10, 0, 0, 0);
                btns[i]->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
                btns[i]->Cursor = System::Windows::Forms::Cursors::Hand;
                btns[i]->Click += handlers[i];
            }

            // Category Headers (Clean ASCII, styled with electric blue accent)
            Label^ header1 = gcnew Label();
            header1->Text = L"  ESSENTIAL ADJUSTMENTS";
            header1->Size = System::Drawing::Size(232, 26);
            header1->ForeColor = System::Drawing::Color::FromArgb(0, 165, 255);
            header1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.5f, System::Drawing::FontStyle::Bold));
            header1->TextAlign = ContentAlignment::MiddleLeft;
            header1->Margin = System::Windows::Forms::Padding(2, 4, 2, 2);

            Label^ header2 = gcnew Label();
            header2->Text = L"  GEOMETRY & TRANSFORM";
            header2->Size = System::Drawing::Size(232, 26);
            header2->ForeColor = System::Drawing::Color::FromArgb(0, 165, 255);
            header2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.5f, System::Drawing::FontStyle::Bold));
            header2->TextAlign = ContentAlignment::MiddleLeft;
            header2->Margin = System::Windows::Forms::Padding(2, 14, 2, 2);

            Label^ header3 = gcnew Label();
            header3->Text = L"  ARTISTIC & STYLIZED";
            header3->Size = System::Drawing::Size(232, 26);
            header3->ForeColor = System::Drawing::Color::FromArgb(0, 165, 255);
            header3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.5f, System::Drawing::FontStyle::Bold));
            header3->TextAlign = ContentAlignment::MiddleLeft;
            header3->Margin = System::Windows::Forms::Padding(2, 14, 2, 2);

            Label^ header4 = gcnew Label();
            header4->Text = L"  COLOR & COMPOSITION";
            header4->Size = System::Drawing::Size(232, 26);
            header4->ForeColor = System::Drawing::Color::FromArgb(0, 165, 255);
            header4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.5f, System::Drawing::FontStyle::Bold));
            header4->TextAlign = ContentAlignment::MiddleLeft;
            header4->Margin = System::Windows::Forms::Padding(2, 14, 2, 2);

            // Section 1: Essential Adjustments (Filters 1, 2, 3, 7)
            this->filterPanel->Controls->Add(header1);
            this->filterPanel->Controls->Add(btn1);
            this->filterPanel->Controls->Add(btn2);
            this->filterPanel->Controls->Add(btn3);
            this->filterPanel->Controls->Add(btn7);

            // Section 2: Geometry & Transform (Filters 5, 6, 8, 11, 17)
            this->filterPanel->Controls->Add(header2);
            this->filterPanel->Controls->Add(btn5);
            this->filterPanel->Controls->Add(btn6);
            this->filterPanel->Controls->Add(btn8);
            this->filterPanel->Controls->Add(btn11);
            this->filterPanel->Controls->Add(btn17);

            // Section 3: Artistic & Stylized (Filters 10, 12, 14, 18)
            this->filterPanel->Controls->Add(header3);
            this->filterPanel->Controls->Add(btn10);
            this->filterPanel->Controls->Add(btn12);
            this->filterPanel->Controls->Add(btn14);
            this->filterPanel->Controls->Add(btn18);

            // Section 4: Color & Composition (Filters 4, 9, 13, 15, 16)
            this->filterPanel->Controls->Add(header4);
            this->filterPanel->Controls->Add(btn4);
            this->filterPanel->Controls->Add(btn9);
            this->filterPanel->Controls->Add(btn13);
            this->filterPanel->Controls->Add(btn15);
            this->filterPanel->Controls->Add(btn16);

            //
            // MyForm
            //
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);
            this->ClientSize = System::Drawing::Size(1020, 640);
            this->Controls->Add(this->filterPanel);
            this->Controls->Add(this->btnSave);
            this->Controls->Add(this->btnLoad);
            this->Controls->Add(this->btnBackward);
            this->Controls->Add(this->btnForward);
            this->Controls->Add(this->pictureBox1);
            this->Controls->Add(this->statusStrip1);
            this->Name = L"MyForm";
            this->Text = L"Baby Photoshop - FCAI";
            this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
            this->MinimumSize = System::Drawing::Size(1020, 650);
            this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);

            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
            this->filterPanel->ResumeLayout(false);
            this->statusStrip1->ResumeLayout(false);
            this->statusStrip1->PerformLayout();
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    private:
        // =============================================
        // THE BRIDGE: C++ pixels -> .NET Bitmap
        // =============================================
        void UpdatePictureBox() {
            if (currentImage->width <= 0 || currentImage->height <= 0) return;

            int w = currentImage->width;
            int h = currentImage->height;

            Bitmap^ bmp = gcnew Bitmap(w, h, PixelFormat::Format24bppRgb);
            System::Drawing::Rectangle rect = System::Drawing::Rectangle(0, 0, w, h);
            BitmapData^ bmpData = bmp->LockBits(rect, ImageLockMode::WriteOnly, bmp->PixelFormat);

            IntPtr ptr = bmpData->Scan0;
            int bytes = Math::Abs(bmpData->Stride) * h;
            cli::array<Byte>^ rgbValues = gcnew cli::array<Byte>(bytes);

            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int stbi_index = (y * w + x) * currentImage->channels;
                    int bmp_index = y * bmpData->Stride + x * 3;

                    // Bitmap expects BGR
                    rgbValues[bmp_index + 2] = currentImage->imageData[stbi_index + 0]; // R
                    rgbValues[bmp_index + 1] = currentImage->imageData[stbi_index + 1]; // G
                    rgbValues[bmp_index + 0] = currentImage->imageData[stbi_index + 2]; // B
                }
            }

            Marshal::Copy(rgbValues, 0, ptr, bytes);
            bmp->UnlockBits(bmpData);
            pictureBox1->Image = bmp;
        }

        // =============================================
        // UNDO / REDO HISTORY SUPPORT
        // =============================================
        void UpdateHistoryButtons() {
            if (history == nullptr) {
                btnBackward->Enabled = false;
                btnForward->Enabled = false;
                btnBackward->BackColor = System::Drawing::Color::FromArgb(45, 45, 48);
                btnForward->BackColor = System::Drawing::Color::FromArgb(45, 45, 48);
                btnBackward->ForeColor = System::Drawing::Color::FromArgb(100, 100, 100);
                btnForward->ForeColor = System::Drawing::Color::FromArgb(100, 100, 100);
                btnBackward->Cursor = System::Windows::Forms::Cursors::Default;
                btnForward->Cursor = System::Windows::Forms::Cursors::Default;
                return;
            }

            bool canBack = history->canBackward();
            bool canFwd = history->canForward();

            btnBackward->Enabled = canBack;
            btnForward->Enabled = canFwd;

            if (canBack) {
                btnBackward->BackColor = System::Drawing::Color::FromArgb(90, 65, 140);
                btnBackward->ForeColor = System::Drawing::Color::White;
                btnBackward->Cursor = System::Windows::Forms::Cursors::Hand;
            } else {
                btnBackward->BackColor = System::Drawing::Color::FromArgb(45, 45, 48);
                btnBackward->ForeColor = System::Drawing::Color::FromArgb(100, 100, 100);
                btnBackward->Cursor = System::Windows::Forms::Cursors::Default;
            }

            if (canFwd) {
                btnForward->BackColor = System::Drawing::Color::FromArgb(90, 65, 140);
                btnForward->ForeColor = System::Drawing::Color::White;
                btnForward->Cursor = System::Windows::Forms::Cursors::Hand;
            } else {
                btnForward->BackColor = System::Drawing::Color::FromArgb(45, 45, 48);
                btnForward->ForeColor = System::Drawing::Color::FromArgb(100, 100, 100);
                btnForward->Cursor = System::Windows::Forms::Cursors::Default;
            }
        }

        // =============================================
        // STATUS TELEMETRY HELPER
        // =============================================
        void UpdateStatusTelemetry(String^ customMsg) {
            if (this->statusLabelMsg == nullptr) return;

            if (!String::IsNullOrEmpty(customMsg)) {
                this->statusLabelMsg->Text = customMsg;
            }

            if (currentImage != nullptr && currentImage->imageData != nullptr && currentImage->width > 0) {
                this->statusLabelDim->Text = String::Format(L"{0} x {1} px", currentImage->width, currentImage->height);
                String^ chText = (currentImage->channels == 1) ? L"1 Channel (Grayscale)" :
                                 (currentImage->channels == 3) ? L"3 Channels (RGB)" :
                                 (currentImage->channels == 4) ? L"4 Channels (RGBA)" :
                                 String::Format(L"{0} Channels", currentImage->channels);
                this->statusLabelChannels->Text = chText;
            } else {
                this->statusLabelDim->Text = L"-- x -- px";
                this->statusLabelChannels->Text = L"-- Channels";
            }

            if (history != nullptr && history->getCurrentNode() != nullptr) {
                int curIdx = history->getCurrentIndex();
                int total = history->getTotalCount();
                int undos = history->getUndoCount();
                int redos = history->getRedoCount();
                this->statusLabelHistory->Text = String::Format(L"History: {0}/{1} (Undo: {2}, Redo: {3})", curIdx, total, undos, redos);
            } else {
                this->statusLabelHistory->Text = L"History: Idle";
            }
        }

        void RecordHistory(String^ actionName) {
            if (history != nullptr && currentImage != nullptr && currentImage->imageData != nullptr) {
                std::string name = msclr::interop::marshal_as<std::string>(actionName);
                history->newImage(*currentImage, name);
                UpdateHistoryButtons();
                UpdateStatusTelemetry(String::Format(L"Applied: {0}", actionName));
            }
        }

        System::Void btnBackward_Click(System::Object^ sender, System::EventArgs^ e) {
            if (history != nullptr && history->canBackward()) {
                Node prevNode = history->backward(1);
                *currentImage = prevNode.image;
                UpdatePictureBox();
                UpdateHistoryButtons();
                String^ action = gcnew String(prevNode.imageName.c_str());
                if (action->Contains(L"\\") || action->Contains(L"/")) {
                    action = System::IO::Path::GetFileName(action);
                }
                UpdateStatusTelemetry(String::Format(L"Undo: Reverted to \"{0}\"", action));
            }
        }

        System::Void btnForward_Click(System::Object^ sender, System::EventArgs^ e) {
            if (history != nullptr && history->canForward()) {
                Node nextNode = history->forward(1);
                *currentImage = nextNode.image;
                UpdatePictureBox();
                UpdateHistoryButtons();
                String^ action = gcnew String(nextNode.imageName.c_str());
                if (action->Contains(L"\\") || action->Contains(L"/")) {
                    action = System::IO::Path::GetFileName(action);
                }
                UpdateStatusTelemetry(String::Format(L"Redo: Advanced to \"{0}\"", action));
            }
        }

        // Helper: check if image is loaded
        bool CheckImageLoaded() {
            if (currentImage->imageData == nullptr || currentImage->width <= 0) {
                MessageBox::Show("Please load an image first!", "No Image", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return false;
            }
            return true;
        }

        // =============================================
        // LOAD & SAVE & EXIT HANDLERS
        // =============================================
        bool PromptAndSaveImage() {
            if (!CheckImageLoaded()) return false;
            SaveFileDialog^ sfd = gcnew SaveFileDialog();
            sfd->Filter = "JPG Image|*.jpg|PNG Image|*.png|BMP Image|*.bmp|TGA Image|*.tga";
            if (sfd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                std::string filepath = msclr::interop::marshal_as<std::string>(sfd->FileName);
                try {
                    currentImage->saveImage(filepath);
                    UpdateStatusTelemetry(String::Format(L"Saved: {0}", System::IO::Path::GetFileName(sfd->FileName)));
                    MessageBox::Show("Image saved successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                    return true;
                } catch (...) {
                    MessageBox::Show("Failed to save image.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    return false;
                }
            }
            return false;
        }

        System::Void MyForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
            if (currentImage != nullptr && currentImage->imageData != nullptr && currentImage->width > 0) {
                System::Windows::Forms::DialogResult result = MessageBox::Show(
                    "Would you like to save the current image before exiting?",
                    "Save before Exit",
                    MessageBoxButtons::YesNoCancel,
                    MessageBoxIcon::Question);

                if (result == System::Windows::Forms::DialogResult::Yes) {
                    bool saved = PromptAndSaveImage();
                    if (!saved) {
                        e->Cancel = true; // User cancelled save file dialog, stay in app
                    }
                }
                else if (result == System::Windows::Forms::DialogResult::Cancel) {
                    e->Cancel = true; // User aborted exit
                }
            }
        }

        void LoadImageFile(String^ filename) {
            std::string filepath = msclr::interop::marshal_as<std::string>(filename);
            try {
                currentImage->loadNewImage(filepath);
                if (history != nullptr) {
                    delete history;
                    history = nullptr;
                }
                history = new ImageHistory(*currentImage, filepath);
                UpdatePictureBox();
                UpdateHistoryButtons();
                pictureBox1->Invalidate();
                UpdateStatusTelemetry(String::Format(L"Loaded: {0}", System::IO::Path::GetFileName(filename)));
            } catch (...) {
                MessageBox::Show("Failed to load image!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        System::Void pictureBox1_DragEnter(System::Object^ sender, System::Windows::Forms::DragEventArgs^ e) {
            if (e->Data->GetDataPresent(DataFormats::FileDrop)) {
                e->Effect = DragDropEffects::Copy;
            } else {
                e->Effect = DragDropEffects::None;
            }
        }

        System::Void pictureBox1_DragDrop(System::Object^ sender, System::Windows::Forms::DragEventArgs^ e) {
            if (e->Data->GetDataPresent(DataFormats::FileDrop)) {
                cli::array<String^>^ files = (cli::array<String^>^)e->Data->GetData(DataFormats::FileDrop);
                if (files != nullptr && files->Length > 0) {
                    String^ droppedFile = files[0];
                    String^ ext = System::IO::Path::GetExtension(droppedFile)->ToLower();
                    if (ext == ".jpg" || ext == ".jpeg" || ext == ".png" || ext == ".bmp" || ext == ".tga") {
                        if (currentImage != nullptr && currentImage->imageData != nullptr && currentImage->width > 0) {
                            System::Windows::Forms::DialogResult res = MessageBox::Show(
                                "Would you like to save the current image before loading a new one?",
                                "Save Current Image",
                                MessageBoxButtons::YesNoCancel,
                                MessageBoxIcon::Question);

                            if (res == System::Windows::Forms::DialogResult::Yes) {
                                bool saved = PromptAndSaveImage();
                                if (!saved) return;
                            }
                            else if (res == System::Windows::Forms::DialogResult::Cancel) {
                                return;
                            }
                        }
                        LoadImageFile(droppedFile);
                    } else {
                        MessageBox::Show("Please drop a valid image file (.jpg, .png, .bmp, .tga).", "Unsupported Format", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    }
                }
            }
        }

        System::Void btnLoad_Click(System::Object^ sender, System::EventArgs^ e) {
            if (currentImage != nullptr && currentImage->imageData != nullptr && currentImage->width > 0) {
                System::Windows::Forms::DialogResult res = MessageBox::Show(
                    "Would you like to save the current image before loading a new one?",
                    "Save Current Image",
                    MessageBoxButtons::YesNoCancel,
                    MessageBoxIcon::Question);

                if (res == System::Windows::Forms::DialogResult::Yes) {
                    bool saved = PromptAndSaveImage();
                    if (!saved) return;
                }
                else if (res == System::Windows::Forms::DialogResult::Cancel) {
                    return;
                }
            }

            OpenFileDialog^ ofd = gcnew OpenFileDialog();
            ofd->Filter = "Image Files|*.jpg;*.jpeg;*.png;*.bmp;*.tga";
            if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                LoadImageFile(ofd->FileName);
            }
        }

        System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e) {
            PromptAndSaveImage();
        }

        // =============================================
        // FILTER 1: Grayscale (no params)
        // =============================================
        System::Void btn1_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            applyGrayscale(*currentImage);
            RecordHistory(L"Grayscale");
            UpdatePictureBox();
        }

        // =============================================
        // FILTER 2: Black & White (no params)
        // =============================================
        System::Void btn2_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            applyBlackAndWhite(*currentImage);
            RecordHistory(L"Black & White");
            UpdatePictureBox();
        }

        // =============================================
        // FILTER 3: Invert (no params)
        // =============================================
        System::Void btn3_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            applyInvert(*currentImage);
            RecordHistory(L"Invert");
            UpdatePictureBox();
        }

        // =============================================
        // FILTER 4: Add Frame (submenu: simple/decorated)
        // =============================================
        System::Void btn4_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            System::Windows::Forms::DialogResult result = MessageBox::Show(
                "Click YES for Simple Frame, NO for Decorated Frame",
                "Add Frame", MessageBoxButtons::YesNoCancel, MessageBoxIcon::Question);
            if (result == System::Windows::Forms::DialogResult::Yes) {
                applyFrame(*currentImage, 1);
                RecordHistory(L"Simple Frame");
                UpdatePictureBox();
            } else if (result == System::Windows::Forms::DialogResult::No) {
                applyFrame(*currentImage, 2);
                RecordHistory(L"Decorated Frame");
                UpdatePictureBox();
            }
        }

        // =============================================
        // FILTER 5: Flip (submenu: horizontal/vertical)
        // =============================================
        System::Void btn5_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            System::Windows::Forms::DialogResult result = MessageBox::Show(
                "Click YES for Horizontal Flip, NO for Vertical Flip",
                "Flip Image", MessageBoxButtons::YesNoCancel, MessageBoxIcon::Question);
            if (result == System::Windows::Forms::DialogResult::Yes) {
                applyFlipHorizontal(*currentImage);
                RecordHistory(L"Horizontal Flip");
                UpdatePictureBox();
            } else if (result == System::Windows::Forms::DialogResult::No) {
                applyFlipVertical(*currentImage);
                RecordHistory(L"Vertical Flip");
                UpdatePictureBox();
            }
        }

        // =============================================
        // FILTER 6: Rotate (text box: 90, 180, 270)
        // =============================================
        System::Void btn6_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            String^ angleStr = Prompt::ShowDialog("Enter rotation angle (90, 180, or 270):", "Rotate Image");
            if (String::IsNullOrEmpty(angleStr)) return;
            try {
                int angle = Int32::Parse(angleStr);
                if (angle == 90 || angle == 180 || angle == 270) {
                    ::Image result = applyRotate(*currentImage, angle);
                    *currentImage = result;
                    RecordHistory(L"Rotate");
                    UpdatePictureBox();
                } else {
                    MessageBox::Show("Please enter 90, 180, or 270.", "Invalid Angle", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                }
            } catch (...) {
                MessageBox::Show("Please enter a valid number.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        // =============================================
        // FILTER 7: Darken/Lighten (submenu + text box for %)
        // =============================================
        System::Void btn7_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            System::Windows::Forms::DialogResult result = MessageBox::Show(
                "Click YES to Darken, NO to Lighten",
                "Darken / Lighten", MessageBoxButtons::YesNoCancel, MessageBoxIcon::Question);

            if (result == System::Windows::Forms::DialogResult::Cancel) return;

            String^ pctStr = Prompt::ShowDialog("Enter percentage (0-100):", "Brightness %");
            if (String::IsNullOrEmpty(pctStr)) return;
            try {
                int pct = Int32::Parse(pctStr);
                if (pct < 0 || pct > 100) {
                    MessageBox::Show("Percentage must be between 0 and 100.", "Invalid", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    return;
                }
                if (result == System::Windows::Forms::DialogResult::Yes) {
                    applyDarken(*currentImage, pct);
                    RecordHistory(L"Darken");
                } else {
                    applyLighten(*currentImage, pct);
                    RecordHistory(L"Lighten");
                }
                UpdatePictureBox();
            } catch (...) {
                MessageBox::Show("Please enter a valid number.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        // =============================================
        // FILTER 8: Resize (dimensions OR scale ratio)
        // =============================================
        System::Void btn8_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;

            System::Windows::Forms::DialogResult mode = MessageBox::Show(
                "Choose Resizing Mode:\n\nClick YES to enter Dimensions (Width & Height)\nClick NO to enter Scale Ratio (e.g. 0.5 for half, 2 for double)",
                "Resize Image",
                MessageBoxButtons::YesNoCancel,
                MessageBoxIcon::Question);

            if (mode == System::Windows::Forms::DialogResult::Cancel) return;

            int newW = 0, newH = 0;

            if (mode == System::Windows::Forms::DialogResult::Yes) {
                // Mode 1: Explicit dimensions
                String^ wStr = Prompt::ShowDialog("Enter new width (pixels):", "Resize - Width");
                if (String::IsNullOrEmpty(wStr)) return;
                String^ hStr = Prompt::ShowDialog("Enter new height (pixels):", "Resize - Height");
                if (String::IsNullOrEmpty(hStr)) return;

                try {
                    newW = Int32::Parse(wStr);
                    newH = Int32::Parse(hStr);
                    if (newW <= 0 || newH <= 0) {
                        MessageBox::Show("Dimensions must be positive.", "Invalid", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                        return;
                    }
                } catch (...) {
                    MessageBox::Show("Please enter valid numbers.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    return;
                }
            }
            else if (mode == System::Windows::Forms::DialogResult::No) {
                // Mode 2: Scale ratio
                String^ ratioStr = Prompt::ShowDialog("Enter scale ratio (e.g. 0.5 for half, 2 for double, max 20):", "Resize - Scale Ratio");
                if (String::IsNullOrEmpty(ratioStr)) return;

                try {
                    double ratio = Double::Parse(ratioStr);
                    if (ratio <= 0.0) {
                        MessageBox::Show("Scale ratio must be positive.", "Invalid", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                        return;
                    }
                    if (ratio > 20.0) {
                        ratio = 20.0;
                    }
                    newW = Math::Max(1, (int)(currentImage->width * ratio));
                    newH = Math::Max(1, (int)(currentImage->height * ratio));
                } catch (...) {
                    MessageBox::Show("Please enter a valid scale ratio.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    return;
                }
            }

            try {
                this->Cursor = Cursors::WaitCursor;
                ::Image result = applyResize(*currentImage, newW, newH);
                *currentImage = result;
                this->Cursor = Cursors::Default;
                RecordHistory(L"Resize");
                UpdatePictureBox();
            } catch (...) {
                this->Cursor = Cursors::Default;
                MessageBox::Show("Failed to resize image.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        // =============================================
        // FILTER 9: Merge (file picker + submenu)
        // =============================================
        System::Void btn9_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;

            // Pick second image
            OpenFileDialog^ ofd = gcnew OpenFileDialog();
            ofd->Title = "Select the second image to merge with";
            ofd->Filter = "Image Files|*.jpg;*.jpeg;*.png;*.bmp;*.tga";
            if (ofd->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;

            std::string filepath = msclr::interop::marshal_as<std::string>(ofd->FileName);
            ::Image img2;
            try {
                img2.loadNewImage(filepath);
            } catch (...) {
                MessageBox::Show("Failed to load second image!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            System::Windows::Forms::DialogResult result = MessageBox::Show(
                "YES = Resize both to biggest dimensions & merge\nNO = Merge common area only (crop)",
                "Merge Mode", MessageBoxButtons::YesNoCancel, MessageBoxIcon::Question);

            if (result == System::Windows::Forms::DialogResult::Cancel) return;

            int mode = (result == System::Windows::Forms::DialogResult::Yes) ? 1 : 2;
            ::Image merged = applyMerge(*currentImage, img2, mode);
            *currentImage = merged;
            RecordHistory(L"Merge");
            UpdatePictureBox();
        }

        // =============================================
        // FILTER 10: Edge Detect (no params)
        // =============================================
        System::Void btn10_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            applyEdgeDetect(*currentImage);
            RecordHistory(L"Edge Detect");
            UpdatePictureBox();
        }

        // =============================================
        // FILTER 11: Crop (drag on image OR manual coordinates)
        // =============================================
        System::Void pictureBox1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
            if (cropInteractionMode && e->Button == System::Windows::Forms::MouseButtons::Left) {
                isSelectingCrop = true;
                cropStartX = e->X;
                cropStartY = e->Y;
                cropCurrentX = e->X;
                cropCurrentY = e->Y;
            }
        }

        System::Void pictureBox1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
            if (cropInteractionMode && isSelectingCrop) {
                cropCurrentX = e->X;
                cropCurrentY = e->Y;
                pictureBox1->Invalidate();
            }
        }

        System::Void pictureBox1_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
            if (cropInteractionMode && isSelectingCrop) {
                isSelectingCrop = false;
                cropInteractionMode = false;
                pictureBox1->Cursor = Cursors::Default;
                pictureBox1->Invalidate();

                if (!CheckImageLoaded()) return;

                int minX = Math::Min(cropStartX, cropCurrentX);
                int maxX = Math::Max(cropStartX, cropCurrentX);
                int minY = Math::Min(cropStartY, cropCurrentY);
                int maxY = Math::Max(cropStartY, cropCurrentY);

                float pbWidth = (float)pictureBox1->ClientSize.Width;
                float pbHeight = (float)pictureBox1->ClientSize.Height;
                float imgWidth = (float)currentImage->width;
                float imgHeight = (float)currentImage->height;

                if (imgWidth <= 0 || imgHeight <= 0 || pbWidth <= 0 || pbHeight <= 0) return;

                float ratio = Math::Min(pbWidth / imgWidth, pbHeight / imgHeight);
                float offsetX = (pbWidth - imgWidth * ratio) / 2.0f;
                float offsetY = (pbHeight - imgHeight * ratio) / 2.0f;

                int sx = (int)Math::Round((minX - offsetX) / ratio);
                int sy = (int)Math::Round((minY - offsetY) / ratio);
                int ex = (int)Math::Round((maxX - offsetX) / ratio);
                int ey = (int)Math::Round((maxY - offsetY) / ratio);

                sx = Math::Max(0, Math::Min(sx, currentImage->width - 1));
                sy = Math::Max(0, Math::Min(sy, currentImage->height - 1));
                ex = Math::Max(1, Math::Min(ex, currentImage->width));
                ey = Math::Max(1, Math::Min(ey, currentImage->height));

                int cw = ex - sx;
                int ch = ey - sy;

                if (cw > 5 && ch > 5) {
                    try {
                        ::Image result = applyCrop(*currentImage, sx, sy, cw, ch);
                        *currentImage = result;
                        RecordHistory(L"Interactive Crop");
                        UpdatePictureBox();
                    } catch (...) {
                        MessageBox::Show("Failed to crop image.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    }
                }
            }
        }

        System::Void pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
            // 1. Draw empty-state screen if no image is currently loaded
            if (currentImage == nullptr || currentImage->imageData == nullptr || currentImage->width <= 0) {
                int pbW = pictureBox1->ClientSize.Width;
                int pbH = pictureBox1->ClientSize.Height;
                if (pbW > 60 && pbH > 60) {
                    e->Graphics->TextRenderingHint = System::Drawing::Text::TextRenderingHint::ClearTypeGridFit;

                    int boxW = Math::Min(500, pbW - 40);
                    int boxH = Math::Min(210, pbH - 40);
                    int boxX = (pbW - boxW) / 2;
                    int boxY = (pbH - boxH) / 2;

                    System::Drawing::Pen^ dashedPen = gcnew System::Drawing::Pen(System::Drawing::Color::FromArgb(75, 75, 82), 2.0f);
                    dashedPen->DashStyle = System::Drawing::Drawing2D::DashStyle::Dash;
                    e->Graphics->DrawRectangle(dashedPen, boxX, boxY, boxW, boxH);
                    delete dashedPen;

                    System::Drawing::Font^ titleFont = gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold);
                    System::Drawing::Font^ subFont = gcnew System::Drawing::Font(L"Segoe UI", 10.5f, System::Drawing::FontStyle::Regular);
                    System::Drawing::Font^ tipFont = gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Regular);

                    System::Drawing::SolidBrush^ titleBrush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(215, 215, 222));
                    System::Drawing::SolidBrush^ subBrush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(150, 150, 158));
                    System::Drawing::SolidBrush^ tipBrush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(0, 150, 255));

                    System::Drawing::StringFormat^ sf = gcnew System::Drawing::StringFormat();
                    sf->Alignment = System::Drawing::StringAlignment::Center;
                    sf->LineAlignment = System::Drawing::StringAlignment::Center;

                    e->Graphics->DrawString(L"No Image Loaded", titleFont, titleBrush, System::Drawing::RectangleF((float)boxX, (float)(boxY + 35), (float)boxW, 35.0f), sf);
                    e->Graphics->DrawString(L"Click \"Load Image\" below or drag & drop an image here", subFont, subBrush, System::Drawing::RectangleF((float)boxX, (float)(boxY + 80), (float)boxW, 30.0f), sf);
                    e->Graphics->DrawString(L"Supported Formats: JPG, PNG, BMP, TGA", tipFont, tipBrush, System::Drawing::RectangleF((float)boxX, (float)(boxY + 125), (float)boxW, 25.0f), sf);

                    delete titleFont;
                    delete subFont;
                    delete tipFont;
                    delete titleBrush;
                    delete subBrush;
                    delete tipBrush;
                    delete sf;
                }
            }

            // 2. Draw interactive crop selection rectangle
            if (isSelectingCrop) {
                int x = Math::Min(cropStartX, cropCurrentX);
                int y = Math::Min(cropStartY, cropCurrentY);
                int w = Math::Abs(cropCurrentX - cropStartX);
                int h = Math::Abs(cropCurrentY - cropStartY);

                if (w > 0 && h > 0) {
                    System::Drawing::Pen^ pen = gcnew System::Drawing::Pen(System::Drawing::Color::Cyan, 2.0f);
                    pen->DashStyle = System::Drawing::Drawing2D::DashStyle::Dash;
                    e->Graphics->DrawRectangle(pen, x, y, w, h);

                    System::Drawing::SolidBrush^ brush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(50, 0, 200, 255));
                    e->Graphics->FillRectangle(brush, x, y, w, h);

                    delete pen;
                    delete brush;
                }
            }
        }

        System::Void btn11_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;

            System::Windows::Forms::DialogResult choice = MessageBox::Show(
                "Choose Cropping Method:\n\nClick YES to Drag on the image with your mouse\nClick NO to enter Coordinates manually",
                "Crop Image",
                MessageBoxButtons::YesNoCancel,
                MessageBoxIcon::Question);

            if (choice == System::Windows::Forms::DialogResult::Cancel) return;

            if (choice == System::Windows::Forms::DialogResult::Yes) {
                cropInteractionMode = true;
                pictureBox1->Cursor = Cursors::Cross;
                UpdateStatusTelemetry(L"Interactive Crop: Drag a selection box over the image");
                MessageBox::Show("Click and drag over the image to select the crop box, then release your mouse.", "Interactive Crop", MessageBoxButtons::OK, MessageBoxIcon::Information);
                return;
            }

            // Mode 2: Manual coordinates
            String^ xStr = Prompt::ShowDialog("Start X coordinate:", "Crop Image");
            if (String::IsNullOrEmpty(xStr)) return;
            String^ yStr = Prompt::ShowDialog("Start Y coordinate:", "Crop Image");
            if (String::IsNullOrEmpty(yStr)) return;
            String^ wStr = Prompt::ShowDialog("Crop width:", "Crop Image");
            if (String::IsNullOrEmpty(wStr)) return;
            String^ hStr = Prompt::ShowDialog("Crop height:", "Crop Image");
            if (String::IsNullOrEmpty(hStr)) return;
            try {
                int sx = Int32::Parse(xStr);
                int sy = Int32::Parse(yStr);
                int cw = Int32::Parse(wStr);
                int ch = Int32::Parse(hStr);
                if (sx < 0 || sy < 0 || cw <= 0 || ch <= 0 ||
                    sx + cw > currentImage->width || sy + ch > currentImage->height) {
                    MessageBox::Show("Crop area is out of bounds!", "Invalid", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    return;
                }
                ::Image result = applyCrop(*currentImage, sx, sy, cw, ch);
                *currentImage = result;
                RecordHistory(L"Crop");
                UpdatePictureBox();
            } catch (...) {
                MessageBox::Show("Please enter valid numbers.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        // =============================================
        // FILTER 12: Blur (submenu: light/medium/strong)
        // =============================================
        System::Void btn12_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            String^ levelStr = Prompt::ShowDialog("Enter blur level (1=Light, 2=Medium, 3=Strong):", "Blur Image");
            if (String::IsNullOrEmpty(levelStr)) return;
            try {
                int level = Int32::Parse(levelStr);
                if (level < 1 || level > 3) {
                    MessageBox::Show("Please enter 1, 2, or 3.", "Invalid", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    return;
                }
                this->Cursor = Cursors::WaitCursor;
                applyBlur(*currentImage, level);
                this->Cursor = Cursors::Default;
                RecordHistory(L"Blur");
                UpdatePictureBox();
            } catch (...) {
                this->Cursor = Cursors::Default;
                MessageBox::Show("Please enter a valid number.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        // =============================================
        // FILTER 13: Sunlight (no params)
        // =============================================
        System::Void btn13_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            applySunlight(*currentImage);
            RecordHistory(L"Sunlight");
            UpdatePictureBox();
        }

        // =============================================
        // FILTER 14: TV / Den Den Mushi (no params)
        // =============================================
        System::Void btn14_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            applyTV(*currentImage);
            RecordHistory(L"TV Effect");
            UpdatePictureBox();
        }

        // =============================================
        // FILTER 15: Purple (no params)
        // =============================================
        System::Void btn15_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            applyPurple(*currentImage);
            RecordHistory(L"Purple");
            UpdatePictureBox();
        }

        // =============================================
        // FILTER 16: Infrared (no params)
        // =============================================
        System::Void btn16_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            applyInfrared(*currentImage);
            RecordHistory(L"Infrared");
            UpdatePictureBox();
        }

        // =============================================
        // FILTER 17: Skew (text box for angle)
        // =============================================
        System::Void btn17_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            String^ angleStr = Prompt::ShowDialog("Enter skew angle in degrees (e.g. 20 to 45):", "Skew Image");
            if (String::IsNullOrEmpty(angleStr)) return;
            try {
                double angle = Double::Parse(angleStr);
                this->Cursor = Cursors::WaitCursor;
                ::Image result = applySkew(*currentImage, angle);
                *currentImage = result;
                this->Cursor = Cursors::Default;
                RecordHistory(L"Skew");
                UpdatePictureBox();
            } catch (...) {
                this->Cursor = Cursors::Default;
                MessageBox::Show("Please enter a valid number.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        // =============================================
        // FILTER 18: Oil Paint (no params, slow)
        // =============================================
        System::Void btn18_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            this->Cursor = Cursors::WaitCursor;
            applyOilPaint(*currentImage);
            this->Cursor = Cursors::Default;
            RecordHistory(L"Oil Paint");
            UpdatePictureBox();
        }
    };
}
