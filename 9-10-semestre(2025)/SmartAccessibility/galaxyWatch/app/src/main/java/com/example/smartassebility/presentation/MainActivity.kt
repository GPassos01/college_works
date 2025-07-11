package com.example.smartassebility.presentation

import android.Manifest
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothManager
import android.bluetooth.le.ScanCallback
import android.bluetooth.le.ScanResult
import android.content.Context
import android.content.pm.PackageManager
import android.os.*
import android.os.VibratorManager
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.result.contract.ActivityResultContracts
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.text.style.TextOverflow
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import androidx.lifecycle.Lifecycle
import androidx.lifecycle.lifecycleScope
import androidx.lifecycle.repeatOnLifecycle
import androidx.wear.compose.material.*
import androidx.compose.ui.tooling.preview.Preview
import com.example.smartassebility.R
import com.example.smartassebility.presentation.theme.SmartAssebilityTheme
import kotlinx.coroutines.launch

class MainActivity : ComponentActivity() {

    private lateinit var bluetoothAdapter: BluetoothAdapter
    private var scanning = mutableStateOf(false)
    private var permissionsGranted = mutableStateOf(false)
    private var vibrator: Vibrator? = null

    private val scanResults = mutableStateListOf<DeviceInfo>()

    data class DeviceInfo(
        val name: String,
        val address: String,
        val rssi: Int
    )

    private val permissionLauncher = registerForActivityResult(
        ActivityResultContracts.RequestMultiplePermissions()
    ) { permissions ->
        permissionsGranted.value = permissions.all { it.value }
    }

    private val scanCallback = object : ScanCallback() {
        override fun onScanResult(callbackType: Int, result: ScanResult?) {
            result?.let {
                val name = if (ActivityCompat.checkSelfPermission(
                        this@MainActivity, 
                        Manifest.permission.BLUETOOTH_CONNECT
                    ) == PackageManager.PERMISSION_GRANTED) {
                    it.device.name ?: "Dispositivo Desconhecido"
                } else {
                    "Dispositivo Desconhecido"
                }
                val address = it.device.address
                val rssi = it.rssi
                val device = DeviceInfo(name, address, rssi)

                // Remove dispositivo existente e adiciona com novo RSSI
                scanResults.removeAll { dev -> dev.address == address }
                scanResults.add(device)

                // Vibra se encontrar qualquer dispositivo (você pode comentar isso se não quiser vibrar para todos)
                vibrate()
            }
        }

        override fun onScanFailed(errorCode: Int) {
            super.onScanFailed(errorCode)
            scanning.value = false
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        val bluetoothManager = getSystemService(Context.BLUETOOTH_SERVICE) as BluetoothManager
        bluetoothAdapter = bluetoothManager.adapter
        
        // Corrigir para API level 30+
        vibrator = if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.S) {
            val vibratorManager = getSystemService(Context.VIBRATOR_MANAGER_SERVICE) as VibratorManager
            vibratorManager.defaultVibrator
        } else {
            @Suppress("DEPRECATION")
            getSystemService(Context.VIBRATOR_SERVICE) as Vibrator
        }

        setContent {
            SmartAssebilityTheme {
                WearApp(
                    scanResults = scanResults,
                    isScanning = scanning.value,
                    permissionsGranted = permissionsGranted.value,
                    onStartScan = { startScan() },
                    onStopScan = { stopScan() },
                    onRequestPermissions = { requestPermissions() }
                )
            }
        }

        checkPermissions()

        // Gerenciar ciclo de vida
        lifecycleScope.launch {
            repeatOnLifecycle(Lifecycle.State.STARTED) {
                // App está visível
            }
        }

        lifecycleScope.launch {
            repeatOnLifecycle(Lifecycle.State.RESUMED) {
                // App está em primeiro plano
            }
        }
    }

    private fun checkPermissions() {
        val permissions = if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.S) {
            arrayOf(
                Manifest.permission.BLUETOOTH_SCAN,
                Manifest.permission.BLUETOOTH_CONNECT,
                Manifest.permission.ACCESS_FINE_LOCATION
            )
        } else {
            arrayOf(
                Manifest.permission.BLUETOOTH,
                Manifest.permission.BLUETOOTH_ADMIN,
                Manifest.permission.ACCESS_FINE_LOCATION
            )
        }

        permissionsGranted.value = permissions.all { permission ->
            ContextCompat.checkSelfPermission(this, permission) == PackageManager.PERMISSION_GRANTED
        }

        if (!permissionsGranted.value) {
            requestPermissions()
        }
    }

    private fun requestPermissions() {
        val permissions = if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.S) {
            arrayOf(
                Manifest.permission.BLUETOOTH_SCAN,
                Manifest.permission.BLUETOOTH_CONNECT,
                Manifest.permission.ACCESS_FINE_LOCATION
            )
        } else {
            arrayOf(
                Manifest.permission.BLUETOOTH,
                Manifest.permission.BLUETOOTH_ADMIN,
                Manifest.permission.ACCESS_FINE_LOCATION
            )
        }

        permissionLauncher.launch(permissions)
    }

    private fun startScan() {
        if (!permissionsGranted.value) {
            requestPermissions()
            return
        }

        if (!scanning.value && bluetoothAdapter.isEnabled) {
            val scanPermission = if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.S) {
                Manifest.permission.BLUETOOTH_SCAN
            } else {
                Manifest.permission.BLUETOOTH_ADMIN
            }
            
            if (ActivityCompat.checkSelfPermission(this, scanPermission) != PackageManager.PERMISSION_GRANTED) {
                return
            }

            scanResults.clear()
            bluetoothAdapter.bluetoothLeScanner?.startScan(scanCallback)
            scanning.value = true
        }
    }

    private fun stopScan() {
        if (scanning.value) {
            val scanPermission = if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.S) {
                Manifest.permission.BLUETOOTH_SCAN
            } else {
                Manifest.permission.BLUETOOTH_ADMIN
            }
            
            if (ActivityCompat.checkSelfPermission(this, scanPermission) == PackageManager.PERMISSION_GRANTED) {
                bluetoothAdapter.bluetoothLeScanner?.stopScan(scanCallback)
            }
            scanning.value = false
        }
    }

    private fun vibrate() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            vibrator?.vibrate(
                VibrationEffect.createOneShot(500, VibrationEffect.DEFAULT_AMPLITUDE)
            )
        } else {
            @Suppress("DEPRECATION")
            vibrator?.vibrate(500)
        }
    }

    override fun onPause() {
        super.onPause()
        stopScan()
    }

    override fun onDestroy() {
        super.onDestroy()
        stopScan()
    }

    companion object {
        private const val PERMISSION_REQUEST_CODE = 1001
    }
}

@Composable
fun WearApp(
    scanResults: List<MainActivity.DeviceInfo>,
    isScanning: Boolean,
    permissionsGranted: Boolean,
    onStartScan: () -> Unit,
    onStopScan: () -> Unit,
    onRequestPermissions: () -> Unit
) {
    // Mostrar TODOS os dispositivos, não apenas os filtrados
    val allDevices = scanResults
    
    // Identificar quais são dispositivos conhecidos (para destacar visualmente)
    val knownDeviceNames = listOf("Raspberry", "SmartAssebility", "SmartAsb", "Smart")
    
    Scaffold(
        timeText = { 
            TimeText(
                modifier = Modifier.padding(top = 4.dp)
            )
        }
    ) {
        Box(
            modifier = Modifier
                .fillMaxSize()
                .padding(16.dp),
            contentAlignment = Alignment.Center
        ) {
            when {
                !permissionsGranted -> {
                    PermissionsScreen(onRequestPermissions)
                }
                
                isScanning -> {
                    ScanningScreen(allDevices.size)
                }
                
                allDevices.isNotEmpty() -> {
                    DevicesFoundScreen(allDevices, knownDeviceNames)
                }
                
                else -> {
                    MainScreen(
                        onStartScan = onStartScan,
                        totalDevices = 0
                    )
                }
            }
            
            // Botões na parte inferior
            if (permissionsGranted) {
                Box(
                    modifier = Modifier
                        .align(Alignment.BottomCenter)
                        .padding(bottom = 8.dp)
                ) {
                    if (isScanning) {
                        Button(
                            onClick = onStopScan,
                            modifier = Modifier.size(48.dp)
                        ) {
                            Text("⏹", fontSize = 20.sp, color = Color.White)
                        }
                    } else {
                        Button(
                            onClick = onStartScan,
                            modifier = Modifier.size(48.dp)
                        ) {
                            Text("🔍", fontSize = 20.sp, color = Color.White)
                        }
                    }
                }
            }
        }
    }
}

@Composable
fun PermissionsScreen(onRequestPermissions: () -> Unit) {
    Column(
        horizontalAlignment = Alignment.CenterHorizontally,
        verticalArrangement = Arrangement.Center
    ) {
        Text(
            text = "🔒",
            fontSize = 32.sp,
            modifier = Modifier.padding(bottom = 8.dp)
        )
        Text(
            text = "Permissões\nNecessárias",
            textAlign = TextAlign.Center,
            style = MaterialTheme.typography.body2,
            modifier = Modifier.padding(bottom = 16.dp)
        )
        Button(
            onClick = onRequestPermissions,
            modifier = Modifier.fillMaxWidth(0.8f)
        ) {
            Text("Permitir", style = MaterialTheme.typography.button)
        }
    }
}

@Composable
fun ScanningScreen(devicesFound: Int) {
    Column(
        horizontalAlignment = Alignment.CenterHorizontally,
        verticalArrangement = Arrangement.Center
    ) {
        CircularProgressIndicator(
            modifier = Modifier.size(48.dp),
            strokeWidth = 4.dp
        )
        
        Spacer(modifier = Modifier.height(16.dp))
        
        Text(
            text = "Procurando...",
            style = MaterialTheme.typography.body1,
            textAlign = TextAlign.Center
        )
        
        if (devicesFound > 0) {
            Text(
                text = "📱 $devicesFound dispositivo${if (devicesFound > 1) "s" else ""} encontrado${if (devicesFound > 1) "s" else ""}",
                style = MaterialTheme.typography.caption1.copy(color = Color.Yellow),
                textAlign = TextAlign.Center,
                modifier = Modifier.padding(top = 8.dp)
            )
        }
    }
}

@Composable
fun DevicesFoundScreen(devices: List<MainActivity.DeviceInfo>, knownDeviceNames: List<String>) {
    Column(
        horizontalAlignment = Alignment.CenterHorizontally,
        verticalArrangement = Arrangement.Center
    ) {
        Text(
            text = "📱",
            fontSize = 40.sp,
            modifier = Modifier.padding(bottom = 8.dp)
        )
        
        Text(
            text = "${devices.size} Dispositivo${if (devices.size > 1) "s" else ""}\nEncontrado${if (devices.size > 1) "s" else ""}!",
            style = MaterialTheme.typography.body1,
            textAlign = TextAlign.Center,
            modifier = Modifier.padding(bottom = 16.dp)
        )
        
        LazyColumn(
            modifier = Modifier.fillMaxWidth(),
            horizontalAlignment = Alignment.CenterHorizontally,
            verticalArrangement = Arrangement.spacedBy(8.dp)
        ) {
            items(devices) { device ->
                val isKnown = knownDeviceNames.any { device.name.contains(it, ignoreCase = true) }
                DeviceCard(device, isKnown)
            }
        }
    }
}

@Composable
fun MainScreen(
    onStartScan: () -> Unit,
    totalDevices: Int
) {
    Column(
        horizontalAlignment = Alignment.CenterHorizontally,
        verticalArrangement = Arrangement.Center
    ) {
        Text(
            text = "🦽",
            fontSize = 48.sp,
            modifier = Modifier.padding(bottom = 8.dp)
        )
        
        Text(
            text = "SmartAssebility",
            style = MaterialTheme.typography.title3,
            textAlign = TextAlign.Center,
            modifier = Modifier.padding(bottom = 8.dp)
        )
        
                    Text(
                text = "Toque para buscar\ndispositivos",
                style = MaterialTheme.typography.body2.copy(color = Color.Gray),
                textAlign = TextAlign.Center,
                modifier = Modifier.padding(bottom = 16.dp)
            )
        
        if (totalDevices > 0) {
                            Text(
                    text = "📱 $totalDevices dispositivo${if (totalDevices > 1) "s" else ""} próximo${if (totalDevices > 1) "s" else ""}",
                    style = MaterialTheme.typography.caption1.copy(color = Color.Yellow),
                    textAlign = TextAlign.Center
                )
        }
    }
}

@Composable
fun DeviceCard(device: MainActivity.DeviceInfo, isKnown: Boolean) {
    Card(
        modifier = Modifier
            .fillMaxWidth(0.9f)
            .padding(2.dp),
        onClick = {}
    ) {
        Column(
            modifier = Modifier
                .padding(8.dp)
                .background(if (isKnown) Color.Green.copy(alpha = 0.2f) else Color.Transparent),
            horizontalAlignment = Alignment.CenterHorizontally
        ) {
            Text(
                text = if (isKnown) "🎯" else "📱",
                fontSize = 20.sp
            )
            Text(
                text = device.name,
                style = MaterialTheme.typography.body2.copy(color = Color.White),
                textAlign = TextAlign.Center,
                maxLines = 1,
                overflow = TextOverflow.Ellipsis
            )
            Text(
                text = "${device.rssi} dBm",
                style = MaterialTheme.typography.caption3.copy(
                    color = when {
                        device.rssi > -50 -> Color.Green
                        device.rssi > -70 -> Color.Yellow  
                        else -> Color.Red
                    }
                )
            )
            if (!isKnown) {
                Text(
                    text = device.address,
                    style = MaterialTheme.typography.caption3.copy(
                        color = Color.Gray,
                        fontSize = 8.sp
                    ),
                    maxLines = 1,
                    overflow = TextOverflow.Ellipsis
                )
            }
        }
    }
}

@Preview(showBackground = true)
@Composable
fun PreviewWearApp() {
    SmartAssebilityTheme {
        WearApp(
            scanResults = listOf(
                MainActivity.DeviceInfo("SmartAssebility-RPi", "AA:BB:CC:DD:EE:FF", -45),
                MainActivity.DeviceInfo("raspberrypi", "11:22:33:44:55:66", -60),
                MainActivity.DeviceInfo("Dispositivo Desconhecido", "99:88:77:66:55:44", -80),
                MainActivity.DeviceInfo("Galaxy Buds", "12:34:56:78:90:AB", -55),
                MainActivity.DeviceInfo("iPhone", "CD:EF:12:34:56:78", -75)
            ),
            isScanning = false,
            permissionsGranted = true,
            onStartScan = {},
            onStopScan = {},
            onRequestPermissions = {}
        )
    }
}
