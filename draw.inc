DRAW_H  = $c4       ; Height Counter
MASK_L  = $C5       ; Left byte mask
MASK_R  = $C6       ; Right byte mask
COLOR_V = $c9

; ==========================================
;  ROUTINE: DrawRect
;  Draws 32x32 box at RECT_X, RECT_Y
; ==========================================
DrawRect:
    ; 1. Calculate Screen Address: BASE + (Y * 40)
    ;    We can use the OS pointer in SAVMSC ($58)
    
    ; 1. Load Y into Pointer
    lda RECT_Y
    sta SCR_PTR
    lda #0
    sta SCR_PTR+1

    ; 2. Calculate Y * 8 (Shift Left 3 times)
    asl SCR_PTR
    rol SCR_PTR+1       ; x2
    asl SCR_PTR
    rol SCR_PTR+1       ; x4
    asl SCR_PTR
    rol SCR_PTR+1       ; x8

    ; 3. Save the "Y*8" result for later
    lda SCR_PTR
    sta TMP_LO
    lda SCR_PTR+1
    sta TMP_HI

    ; 4. Continue shifting to get Y * 32 (Shift Left 2 more times)
    asl SCR_PTR
    rol SCR_PTR+1       ; x16
    asl SCR_PTR
    rol SCR_PTR+1       ; x32

    ; 5. Add them together: (Y*32) + (Y*8) = Y*40
    lda SCR_PTR
    clc
    adc TMP_LO
    sta SCR_PTR
    lda SCR_PTR+1
    adc TMP_HI
    sta SCR_PTR+1

    ; 6. Add Screen Base Address ($3000)
    ;    Low byte of $3000 is 0, so we only add High byte
    lda SCR_PTR+1
    clc
    adc ActualBufferAddr + 1            ; High byte of $3000
    sta SCR_PTR+1

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
    lda COLOR_V
    
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
    clc
    lda SCR_PTR
    adc #40
    sta SCR_PTR
    bcc NextLine
    inc SCR_PTR+1
NextLine:
    dec DRAW_H
    bne DrawLoop
    
    rts
