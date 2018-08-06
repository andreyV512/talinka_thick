object ManageForm: TManageForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077' '#1091#1089#1090#1088#1086#1081#1089#1090#1074#1072#1084#1080
  ClientHeight = 198
  ClientWidth = 321
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDefault
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object gbThickness: TGroupBox
    Left = 18
    Top = 24
    Width = 283
    Height = 115
    Caption = #1052#1086#1076#1091#1083#1100' '#1090#1086#1083#1097#1080#1085#1099' '#1089#1090#1077#1085#1082#1080
    TabOrder = 0
    object bRotation: TBitBtn
      Left = 3
      Top = 46
      Width = 113
      Height = 49
      Caption = #1042#1088#1072#1097#1072#1090#1100
      DoubleBuffered = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentDoubleBuffered = False
      ParentFont = False
      TabOrder = 0
      OnClick = bRotationClick
      OnKeyPress = FormKeyPress
    end
    object cbRL: TCheckBox
      Left = 152
      Top = 24
      Width = 97
      Height = 17
      Caption = 'RL'
      TabOrder = 1
    end
    object cbRM: TCheckBox
      Left = 152
      Top = 47
      Width = 97
      Height = 17
      Caption = 'RM'
      TabOrder = 2
    end
    object cbRH: TCheckBox
      Left = 152
      Top = 72
      Width = 97
      Height = 17
      Caption = 'RH'
      TabOrder = 3
    end
  end
  object StatusBarBottom: TStatusBar
    AlignWithMargins = True
    Left = 3
    Top = 164
    Width = 315
    Height = 31
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Tahoma'
    Font.Style = []
    Panels = <
      item
        Width = 600
      end
      item
        Width = 400
      end>
    ParentColor = True
    UseSystemFont = False
  end
end
