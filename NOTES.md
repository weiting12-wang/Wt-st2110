# 2025-07-31

1. 修改wt_tx_create, 將video, audio, ...等payload格式參數分離到wt_tx_set_video_format等函數
2. 移除wt_frame_t, 目前不支持, 未來如須支持, 應考慮multi-planar格式, 如NV12, YV12及聲音格式
3. 修改wt_tx_push_xxx為wt_tx_send_xxx, 並將packet封裝為wt_packet_t
4. 修改wt_rx_create, 同wt_tx_create
5. 增加wt_rx_connection_status_callback_t, 提供連線狀態回呼
6. 增加wt_rx_get_xxx_format, 用於連線後取得各種資料格式
