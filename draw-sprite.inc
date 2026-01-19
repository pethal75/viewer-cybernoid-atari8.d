;----------------------------------
; Input parameters
;----------------------------------

DrawSprite_16x16_XOR:
    ;----------------------------------
    ; SCR_PTR = Screen + Y*40 + X
    ;----------------------------------
    lda SPR_Y
    tay
    lda RowLo,y
    clc
    adc SPR_X
    sta SCR_PTR
    lda RowHi,y
    adc ActualBufferAddr+1
    sta SCR_PTR+1

    ldx #16         ; row counter

    lda SPR_PTR
    sta TMP_PTR
    lda SPR_PTR + 1
    sta TMP_PTR + 1
    
RowLoop:
; ===== 4 BYTES PER ROW (UNROLLED) =====
    ldy #0          ; sprite data index

    lda (SCR_PTR),y
    eor (TMP_PTR),y
    sta (SCR_PTR),y
    iny

    lda (SCR_PTR),y
    eor (TMP_PTR),y
    sta (SCR_PTR),y
    iny

    lda (SCR_PTR),y
    eor (TMP_PTR),y
    sta (SCR_PTR),y
    iny

    lda (SCR_PTR),y
    eor (TMP_PTR),y
    sta (SCR_PTR),y
    iny

; ===== next screen row =====

    clc
    lda SCR_PTR
    adc #40
    sta SCR_PTR
    bcc NoCarry
    inc SCR_PTR+1
NoCarry:

; ===== next sprite row =====
    clc
    lda TMP_PTR
    adc #4
    sta TMP_PTR
    bcc NoCarry2
    inc TMP_PTR+1
NoCarry2:

    dex
    bne RowLoop
    rts

RowLo:
    .byte $00,$28,$50,$78,$A0,$C8,$F0,$18
    .byte $40,$68,$90,$B8,$E0,$08,$30,$58
    .byte $80,$A8,$D0,$F8,$20,$48,$70,$98
    .byte $C0,$E8,$10,$38,$60,$88,$B0,$D8
    .byte $00,$28,$50,$78,$A0,$C8,$F0,$18
    .byte $40,$68,$90,$B8,$E0,$08,$30,$58
    .byte $80,$A8,$D0,$F8,$20,$48,$70,$98
    .byte $C0,$E8,$10,$38,$60,$88,$B0,$D8
    .byte $00,$28,$50,$78,$A0,$C8,$F0,$18
    .byte $40,$68,$90,$B8,$E0,$08,$30,$58
    .byte $80,$A8,$D0,$F8,$20,$48,$70,$98
    .byte $C0,$E8,$10,$38,$60,$88,$B0,$D8

RowHi:
    .byte $00,$00,$00,$00,$00,$00,$00,$01
    .byte $01,$01,$01,$01,$01,$02,$02,$02
    .byte $02,$02,$02,$02,$03,$03,$03,$03
    .byte $03,$03,$04,$04,$04,$04,$04,$04
    .byte $05,$05,$05,$05,$05,$05,$05,$06
    .byte $06,$06,$06,$06,$06,$07,$07,$07
    .byte $07,$07,$07,$07,$08,$08,$08,$08
    .byte $08,$08,$09,$09,$09,$09,$09,$09
    .byte $0A,$0A,$0A,$0A,$0A,$0A,$0A,$0B
    .byte $0B,$0B,$0B,$0B,$0B,$0C,$0C,$0C
    .byte $0C,$0C,$0C,$0C,$0D,$0D,$0D,$0D
    .byte $0D,$0D,$0E,$0E,$0E,$0E,$0E,$0E