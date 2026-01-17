RECT_X  = $CB       ; Input X (0-159)
RECT_Y  = $CC       ; Input Y (0-96)
DRAW_H  = $CD       ; Height Counter
MASK_L  = $CE       ; Left byte mask
MASK_R  = $CF       ; Right byte mask
SCR_PTR = $D0       ; Calculation pointer (2 bytes)
COLOR_V = $55
Buffer1 = $3000
Buffer2 = $4000

; ==========================================
;  ROUTINE: DrawRect
;  Draws 32x32 box at RECT_X, RECT_Y
; ==========================================
DrawRect:
    ; 1. Calculate Screen Address: BASE + (Y * 40)
    ;    We can use the OS pointer in SAVMSC ($58)
    
    lda #<Buffer1      ; Load Low Byte of screen base
    sta SCR_PTR
    lda #>Buffer1    ; Load High Byte
    sta SCR_PTR+1

    ldy RECT_Y      ; Loop Y times to add 40 per line
    beq CalcX       ; Skip if Y=0
AddYLine:
    lda SCR_PTR
    clc
    adc #40         ; Add 40 bytes (width of Mode 7)
    sta SCR_PTR
    bcc NoCarry
    inc SCR_PTR+1
NoCarry:
    dey
    bne AddYLine

CalcX:
    ; 2. Calculate Byte Offset for X
    ;    X is in pixels. 4 pixels per byte.
    ;    Byte Offset = X / 4
    
    lda RECT_X
    lsr             ; / 2
    lsr             ; / 4
    tay             ; Y = Byte Offset

    ; 3. Handle Pixel Alignment (Sub-byte precision)
    ;    We need to calculate masks for the left and right edges
    ;    because X might not be divisible by 4.
    
    ; Note: For a 32-pixel width (exactly 8 bytes), 
    ; if X%4 == 0, we write exactly 8 bytes.
    ; if X%4 != 0, we touch 9 bytes total (partial left, 7 full, partial right).
    
    ; Simplified approach for demo:
    ; Since width is 32 (multiple of 4), logic is easier.
    ; We just write 8 full bytes starting at the calculated offset.
    ; *To support smooth per-pixel movement, we would shift bits.*
    ; *This version snaps to nearest byte (X/4) for speed/simplicity size code.*
    ; *If you strictly need per-pixel precision, let me know, it requires shifting masks.*

    lda #16
    sta DRAW_H

DrawLoop:
    ; Y contains the byte offset (column)
    ; SCR_PTR points to the start of the current line
    
    ; Draw 8 bytes (32 pixels)
    lda #COLOR_V
    
    sta (SCR_PTR),y
    iny
    sta (SCR_PTR),y
    iny
    sta (SCR_PTR),y
    iny
    sta (SCR_PTR),y
    iny
    
    ; Restore Y index for next line (move back 7 bytes)
    tya
    sec
    sbc #4
    tay

    ; Move SCR_PTR to next line (+40)
    lda SCR_PTR
    clc
    adc #40
    sta SCR_PTR
    bcc NextLine
    inc SCR_PTR+1
NextLine:
    dec DRAW_H
    bne DrawLoop
    
    rts
