import pandas as pd
import plotly.graph_objects as go
import numpy as np

# 1. Load data
df = pd.read_csv("simulation_log.csv")

# 2. Calculate global min/max for axes to prevent the camera from jumping
def get_range(col_target, col_interceptor, padding=0.05):
    min_val = min(df[col_target].min(), df[col_interceptor].min())
    max_val = max(df[col_target].max(), df[col_interceptor].max())
    pad_val = (max_val - min_val) * padding
    # Fallback padding if min == max
    if pad_val == 0: pad_val = 10 
    return [min_val - pad_val, max_val + pad_val]

range_x = get_range("TargetX", "InterceptorX")
range_y = get_range("TargetY", "InterceptorY")
range_z = get_range("TargetZ", "InterceptorZ")

# 3. Create the Base Figure (Frame 0)
# mode='lines+markers' but marker only shows at the very tip (the current position)
fig = go.Figure(
    data=[
        go.Scatter3d(
            x=[df["TargetX"].iloc[0]], y=[df["TargetY"].iloc[0]], z=[df["TargetZ"].iloc[0]],
            mode='lines+markers',
            name='Target',
            line=dict(color='red', width=2, dash='dash'),
            marker=dict(size=2, color='red')
        ),
        go.Scatter3d(
            x=[df["InterceptorX"].iloc[0]], y=[df["InterceptorY"].iloc[0]], z=[df["InterceptorZ"].iloc[0]],
            mode='lines+markers',
            name='Interceptor',
            line=dict(color='blue', width=2),
            marker=dict(size=2, color='blue')
        )
    ]
)

# 4. Generate the Frames
# If CSV file has thousands of rows, generating a frame for every single row might be slow.
# Change `step = 1` to `step = 5` or `10` to skip rows and speed up rendering.
step = 1 
frames = []
# Define default marker styles
target_color = 'red'
target_size = 2
target_symbol = 'circle'
interceptor_color = 'blue'
interceptor_size = 2
interceptor_symbol = 'circle'

for k in range(1, len(df), step):
    # 1. Check the hit status for the current frame
    hit_occurred = df["IsHit"].iloc[k]
       
    # 2. If a hit occurred, change the visual properties to simulate an explosion
    if hit_occurred:
        target_color = 'orange'
        target_size = 2       
        target_symbol = 'x'    # Change the shape

    frames.append(
        go.Frame(
            data=[
                # Target Trace
                go.Scatter3d(
                    x=df["TargetX"].iloc[:k], 
                    y=df["TargetY"].iloc[:k], 
                    z=df["TargetZ"].iloc[:k],
                    marker=dict(size=target_size, color=target_color, symbol=target_symbol)
                ),
                # Interceptor Trace
                go.Scatter3d(
                    x=df["InterceptorX"].iloc[:k], 
                    y=df["InterceptorY"].iloc[:k], 
                    z=df["InterceptorZ"].iloc[:k],
                    marker=dict(size=interceptor_size, color=interceptor_color, symbol=interceptor_symbol)
                )
            ],
            name=str(k)
        )
    )

fig.frames = frames

# 5. Configure Layout and Animation Buttons
fig.update_layout(
    title="Luftverteidigungssimulation: 3D Animation",
    scene=dict(
        xaxis=dict(range=range_x, title="X-Position [m]"),
        yaxis=dict(range=range_y, title="Y-Position [m]"),
        zaxis=dict(range=range_z, title="Z-Position [m]"),
        aspectmode='cube' # Forces the 3D box to be a perfect cube
    ),
    updatemenus=[dict(
        type="buttons",
        showactive=False,
        y=0,
        x=0,
        xanchor="left",
        yanchor="top",
        pad=dict(t=50, r=10),
        buttons=[
            dict(
                label="Play",
                method="animate",
                args=[None, dict(frame=dict(duration=50, redraw=True), 
                                 transition=dict(duration=0), 
                                 fromcurrent=True, 
                                 mode='immediate')]
            ),
            dict(
                label="Pause",
                method="animate",
                args=[[None], dict(frame=dict(duration=0, redraw=False), 
                                   mode='immediate', 
                                   transition=dict(duration=0))]
            )
        ]
    )]
)

# 6. Display the plot in the browser
fig.show()

# Optional: To save this interactive animation as an HTML file you can share with others
# fig.write_html("3d_simulation.html")