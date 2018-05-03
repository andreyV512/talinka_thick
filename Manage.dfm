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
    object Label4: TLabel
      Left = 160
      Top = 40
      Width = 72
      Height = 13
      Caption = #1057#1082#1086#1088#1086#1089#1090#1100' '#1074' '#1043#1094
    end
    object bRotation: TBitBtn
      Left = 35
      Top = 38
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
    object eFriquencyRot: TEdit
      Left = 160
      Top = 66
      Width = 107
      Height = 21
      NumbersOnly = True
      TabOrder = 1
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
    ExplicitTop = 254
    ExplicitWidth = 584
  end
end
