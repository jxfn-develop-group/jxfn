package edu.jxfn.jxfn

import android.Manifest
import android.content.Intent
import android.content.pm.PackageManager
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.net.Uri
import android.os.Bundle
import android.os.Environment
import android.provider.MediaStore
import android.support.design.widget.Snackbar
import android.support.design.widget.NavigationView
import android.support.v4.app.ActivityCompat
import android.support.v4.content.ContextCompat
import android.support.v4.content.FileProvider
import android.support.v4.view.GravityCompat
import android.support.v7.app.ActionBarDrawerToggle
import android.support.v7.app.AppCompatActivity
import android.view.Menu
import android.view.MenuItem
import com.github.kittinunf.fuel.Fuel
import kotlinx.android.synthetic.main.activity_main.*
import kotlinx.android.synthetic.main.app_bar_main.*
import kotlinx.android.synthetic.main.content_main.*
import java.io.File
import java.io.FileInputStream
import java.nio.charset.Charset

class Main : AppCompatActivity(), NavigationView.OnNavigationItemSelectedListener {
    val cameraRequestCode: Int = 0
    var bitmap: Bitmap? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        setSupportActionBar(toolbar)

        fab.setOnClickListener {
            bitmapProcess(bitmap)
        }

        val toggle = ActionBarDrawerToggle(
                this, drawer_layout, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close)
        drawer_layout.addDrawerListener(toggle)
        toggle.syncState()

        nav_view.setNavigationItemSelectedListener(this)
    }

    override fun onBackPressed() {
        if (drawer_layout.isDrawerOpen(GravityCompat.START)) {
            drawer_layout.closeDrawer(GravityCompat.START)
        } else {
            super.onBackPressed()
        }
    }

    override fun onCreateOptionsMenu(menu: Menu): Boolean {
        // Inflate the menu; this adds items to the action bar if it is present.
        menuInflater.inflate(R.menu.main, menu)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        when (item.itemId) {
            R.id.action_settings -> return true
            else -> return super.onOptionsItemSelected(item)
        }
    }

    override fun onNavigationItemSelected(item: MenuItem): Boolean {
        // Handle navigation view item clicks here.
        when (item.itemId) {
            R.id.nav_camera -> {
                capturePhoto()
                // Handle the camera action
            }
            R.id.nav_gallery -> {

            }
            R.id.nav_slideshow -> {

            }
            R.id.nav_manage -> {

            }
            R.id.nav_share -> {

            }
            R.id.nav_send -> {

            }
        }

        drawer_layout.closeDrawer(GravityCompat.START)
        return true
    }

    fun capturePhoto(): Unit {
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE)
                != PackageManager.PERMISSION_GRANTED) {
            //申请WRITE_EXTERNAL_STORAGE权限
            val writeExternalStorage: Array<String> =
                    arrayOf(Manifest.permission.WRITE_EXTERNAL_STORAGE)
            val WRITE_EXTERNAL_STORAGE_REQUEST_CODE: Int = 0
            ActivityCompat.requestPermissions(
                    this, writeExternalStorage, WRITE_EXTERNAL_STORAGE_REQUEST_CODE)
        }
        else{
            capturePhotoNext()
        }
    }

    override fun onRequestPermissionsResult(
            requestCode: Int, permissions: Array<out String>, grantResults: IntArray) {
        val writeExternalStorage: Int = 0
        if (requestCode == writeExternalStorage) {
            if (grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                capturePhotoNext()
            }
        }
    }

    fun capturePhotoNext(): Unit {
        textView1.text = "success!"
        val imagePath: File = File(Environment.getExternalStorageDirectory(), "Jxfn")
        if (!imagePath.exists())
            imagePath.mkdirs()
        val newFile = File(imagePath, "myCamera.jpg")
        val contentUri: Uri = FileProvider.getUriForFile(
                this, "edu.jxfn.fileprovider", newFile
        )
        val intent: Intent = Intent(MediaStore.ACTION_IMAGE_CAPTURE)
        intent.putExtra(MediaStore.EXTRA_OUTPUT, contentUri)
        startActivityForResult(intent, cameraRequestCode)
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        if (requestCode == cameraRequestCode) {
            val imagePath: File = File(Environment.getExternalStorageDirectory(), "Jxfn")
            if(!imagePath.exists()) {
                textView1.text = "Error!"
                return
            }
            val file = File(imagePath, "myCamera.jpg")
            val newFile: FileInputStream = FileInputStream(file)
            val newBitmap = BitmapFactory.decodeStream(newFile)
            newFile.close()
            // bitmap = bitmapProcess(bitmap)
            imageView2.setImageBitmap(newBitmap)
            bitmap = newBitmap
        }
    }

    fun translate(word: String): Unit {
        val url: String = "https://translation.googleapis.com/language/translate/v2"
        val param = listOf(
                "key" to "AIzaSyBt9NFvN8wqyVDgXiw8wN41wtTDntxootg",
                "target" to "zh-CN",
                "source" to "en",
                "q" to word
        )
        Fuel.post(url, param).response { request, response, result ->
            //do something with response
            val (res, err) = result
            if (res == null) {
                textView1.text = "No Internet Connect"
            }
            else {
                val resText = res!!.toString(charset("utf-8"))
                val regexString = Regex(""""translatedText": "(.*)"""")
                val regexResult = regexString.find(resText)
                textView1.text = regexResult!!.groupValues[1]
            }
        }
    }

    fun bitmapProcess(bitmap: Bitmap?): Unit {
        if (bitmap == null) {
            Snackbar.make(nav_view, "Please choose a photo first", Snackbar.LENGTH_LONG).
                    setAction("Action", null).show()
            return
        }

        imageView2.setImageBitmap(null)
        translate("hello world.")
    }
}
